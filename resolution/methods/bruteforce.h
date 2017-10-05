#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "resolution/solution.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

Solution bruteForceSearch(std::vector<Coordinate> &cities, int startCity,
                          std::function<void(const Solution&)> setSolution,
                          std::function<void(std::string)> log,
                          std::function<void(double)> chartLog,
                          std::function<void(std::string)> logIterations,
                          std::function<bool()> stopRequested ) {
    Solution currentSol;
    currentSol.path.push_back(startCity);
    for(size_t i = 0; i < cities.size(); i++)
        if(i != startCity)
            currentSol.path.push_back(i);

    // possibilites
    unsigned long long possibilities = 1;
    for (size_t i = 2; i <= cities.size()-1; ++i){
        possibilities *= i;
    }
    unsigned long long count = 1;

    // expectancy
    long double expectation = 0;
//    size_t perSecond = 0;
    size_t countPerSecond = 1;
    auto last = std::chrono::steady_clock::now();

    Solution bestSol;
    auto start = std::chrono::steady_clock::now();
    do {
        currentSol.distance = getPathDistance(cities, currentSol.path);

        if(currentSol.distance < bestSol.distance) {
            bestSol = currentSol;
            auto now = std::chrono::steady_clock::now();
            double seconds = std::chrono::duration<double>(now-start).count();
            log( "[ "+ std::to_string(seconds) +" segundos ] Distância melhorada: " + std::to_string(currentSol.distance) );
        }

        setSolution( currentSol );
        chartLog( currentSol.distance );

        if ( std::chrono::steady_clock::now() - last > std::chrono::seconds(1) ){
            expectation = ((double) (possibilities-count) / (double) countPerSecond) / 60. / 60. / 24. / 365.;
//            perSecond = countPerSecond;
            countPerSecond = 0;
            last = std::chrono::steady_clock::now();
        }
//        double percent = ((double) count / (double) possibilities) * 100;
        std::stringstream ss;
        ss.imbue(std::locale("pt_BR.UTF-8"));
        ss << count << "/" << possibilities
//           << "   " << std::fixed << std::setprecision(2) << percent << "%"
//           << "   " << perSecond << " per second"
           << "   " << std::fixed << std::setprecision(0) << expectation << " anos";
        logIterations( ss.str() );
        ++count;
        ++countPerSecond;

    } while( std::next_permutation(currentSol.path.begin() + 1, currentSol.path.end()) && !stopRequested() );
    log( "Melhor distância encontrada: " + std::to_string(bestSol.distance) );
    return bestSol;
}

#endif
