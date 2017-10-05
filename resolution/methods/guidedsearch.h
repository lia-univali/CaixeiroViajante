#ifndef GUIDEDSEARCH
#define GUIDEDSEARCH

#include "resolution/solution.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <map>
#include <iostream>

using Cities = std::vector<Coordinate>;

struct GSolution : public Solution {

};

double deltaCity(GSolution &sol, Cities &cities, size_t cityIndex){
    double distance = 0.0;
    if ( cityIndex == 0 ){
        distance += euclidianDistance( cities.at(sol.path.back()), cities.at(sol.path.at(cityIndex)) );
    } else {
        distance += euclidianDistance( cities.at(sol.path.at(cityIndex-1)), cities.at(sol.path.at(cityIndex)) );
    }
    if ( cityIndex == sol.path.size()-1 ){
        distance += euclidianDistance( cities.at(sol.path.front()), cities.at(sol.path.at(cityIndex)) );
    } else {
        distance += euclidianDistance( cities.at(sol.path.at(cityIndex+1)), cities.at(sol.path.at(cityIndex)) );
    }
    return distance;
}

Solution getNeighbor(const GSolution &sol, Cities &cities, std::function<double(GSolution&)> objective, bool &improved){
    Solution best = sol;
    improved = false;
    #pragma omp parallel for
    for (size_t i = 0; i < cities.size(); ++i) {
        for (size_t j = 0; j < cities.size(); ++j) {
            if ( i < j ){
                GSolution neighbor = sol;

                neighbor.distance -= deltaCity( neighbor, cities, i );
                neighbor.distance -= deltaCity( neighbor, cities, j );
                //
                std::swap( neighbor.path.at(i), neighbor.path.at(j) );
                //
                neighbor.distance += deltaCity( neighbor, cities, i );
                neighbor.distance += deltaCity( neighbor, cities, j );

                if ( objective(neighbor) < objective(best) ){
                    best = neighbor;
                    improved = true;
                }
            }
        }
    }
    return best;
}

GSolution localSearch(Cities &cities,
                     GSolution sol,
                     std::function<double(GSolution&)> objective,
                     std::function<void(const Solution&)> setSolution,
                     std::function<void(std::string)> log,
                     std::function<void(double)> chartLog,
                     std::function<void(std::string)> logIterations,
                     std::function<bool()> stopRequested){
    GSolution best = sol;

    size_t it = 0;
    bool improved = false;
    do {
        sol = getNeighbor( sol, cities, objective, improved );
        if ( sol.distance < best.distance ){
            best = sol;
            log( "Melhorado: " + std::to_string( sol.distance ) );
        }
        ++it;
        setSolution( sol );
        chartLog( sol.distance );
        logIterations( std::to_string(it) );

    } while ( !stopRequested() && improved );
    return best;
}

Solution guidedSearch(Cities &cities,
                          std::function<void(const Solution&)> setSolution,
                          std::function<void(std::string)> log,
                          std::function<void(double)> chartLog,
                          std::function<void(std::string)> logIterations,
                          std::function<bool()> stopRequested
                ) {

    GSolution sol;
    sol.path.reserve(cities.size());
    for (size_t i = 0; i < cities.size(); ++i) {
        sol.path.emplace_back(i);
    }
    std::random_shuffle( sol.path.begin(), sol.path.end() );
    sol.distance = getPathDistance( cities, sol.path );

    const double lambda = 1.0;
    const size_t maxIterations = 50; // without improvement


//    size_t M = ( cities.size() * cities.size()-1 )/2; // n of edges


    auto doPair = []( size_t a, size_t b ) -> std::pair<size_t,size_t> { return std::minmax( a, b ); };

    std::map<std::pair<size_t,size_t>, double > cost;
    std::map<std::pair<size_t,size_t>, double > penalties;

    for (size_t i = 0; i < cities.size(); ++i){
        for (size_t j = 0; j < cities.size(); ++j){
            if ( i < j ){
                cost[ doPair(i,j) ] = euclidianDistance( cities.at(i), cities.at(j) );
                penalties[ doPair(i,j) ] = 0.0;
            }
        }
    }

    /// I[] // if have feature
    std::function<bool(GSolution&,size_t,size_t)> haveFeature = [&](GSolution &sol, size_t a, size_t b) -> bool {
        if ( sol.path.front() == a ){
            return ( sol.path.at(1) == b );
        }
        if ( sol.path.back() == a ){
            return ( sol.path.at( sol.path.size()-2 ) == b );
        }
        for (size_t i = 1; i < sol.path.size()-1; ++i){
            if ( sol.path.at(i) == a ){
                if ( sol.path.at(i-1) == b || sol.path.at(i+1) == b ){
                    return true;
                }
            }
        }
        return false;
    };
    /// objective
    std::function<double(GSolution&)> objectiveFunction = [&](GSolution &sol){
        double sum = 0.0;
        size_t previous = sol.path.size()-1;
        for (size_t i = 0; i < sol.path.size(); ++i){
            auto par = doPair( sol.path.at(previous), sol.path.at(i) );
            sum += penalties.at( par );
            previous = i;
        }
        return sol.distance + lambda*sum;
    };
    /// util
    std::function<double(GSolution&,size_t,size_t)> util = [&](GSolution &sol, size_t a, size_t b) -> double {
        if ( haveFeature(sol,a,b) ){
            return cost.at(doPair(a,b)) / ( 1 + penalties.at( doPair(a,b) ) );
        }
        return 0.0;
    };


    std::map<std::pair<size_t,size_t>, double> utils;

    /// search
    GSolution best = sol;
    for (size_t it = 1; it <= maxIterations && !stopRequested(); ++it){
        log( "-" + std::to_string(it) + "-------------" );
        sol = localSearch( cities, sol, objectiveFunction, setSolution, log, chartLog, logIterations, stopRequested );
        if ( sol.distance < best.distance ){
            it = 1;
            best = sol;
        }
        // calculate utils and find maximum
        double max = 0.0;
//        for (size_t i = 0; i < cities.size(); ++i){
//            for (size_t j = 0; j < cities.size(); ++j){
//                if (i < j){
//                    utils[ doPair(i,j) ] = util(sol,i,j);
//                    if ( utils[ doPair(i,j) ] > max ){
//                        max = utils[ doPair(i,j) ];
//                    }
//                }
//            }
//        }
        size_t previous = sol.path.size()-1;
        for (size_t i = 0; i < sol.path.size(); ++i){
            auto pair = doPair( sol.path.at(previous), sol.path.at(i) );
            utils[ pair ] = cost.at(pair) / ( 1 + penalties.at( pair ) );
            if ( utils[ pair ] > max ){
                max = utils[ áir ];
            }
            previous = i;
        }
        // navigate through maximum // increase penalties
        for (const auto &ut : utils){
            if ( haveFeature( sol, ut.first.first, ut.first.second ) ){
                penalties.at( doPair(ut.first.first, ut.first.second) ) += 1.0;
            }
        }
    }
    log( "Melhor encontrado: " + std::to_string(best.distance) );
    setSolution(best);
    return best;
}


#endif // GUIDEDSEARCH
