#ifndef SETUPALGORITHMS_H
#define SETUPALGORITHMS_H

#include "toolbox.h"
#include "bruteforce.h"
#include "iteratedSearch.h"
#include "minimumLocalRoute.h"

void setupAlgorithms(std::vector<ToolBox::AlgorithmData> &algorithms){
    {
        ToolBox::AlgorithmData test;
        test.name = "Teste";
        test.run = [](
                GraphicData&,
                int initialNode,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            srand(time(NULL));
            int i = 0;
            while ( !stopRequested() && i < 1000*1000 ){
                double y = (double) rand() - RAND_MAX/2.;
                chartLog( y );
                log( "["+std::to_string(i) +"]:  "+ std::to_string(y) );
                ++i;
//                std::this_thread::sleep_for( std::chrono::milliseconds(20) );
            }
            onFinish();
        };
        algorithms.emplace_back(test);
    }
    {
        ToolBox::AlgorithmData bruteForce;
        bruteForce.name = "Força Bruta";
        bruteForce.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = bruteForceSearch(g, initialNode, log, chartLog, stopRequested);
            onFinish();
        };
        algorithms.emplace_back(bruteForce);
    }
    {
        ToolBox::AlgorithmData constructive;
        constructive.name = "Cidade mais Próxima";
        constructive.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {

            Solution s = minimumLocalRoute(g, initialNode, log, chartLog, stopRequested);
            onFinish();
        };
        algorithms.emplace_back(constructive);

    }
    {
        ToolBox::AlgorithmData iterated;
        iterated.name = "Busca Iterada";
        iterated.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = iteratedSearch(
                        g,    // coordinates
                        1000, // n iterations
                        g.size()*0.3,    // num. of disturbance
                        log, chartLog, stopRequested
            );
            onFinish();
        };
        algorithms.emplace_back(iterated);
    }

}

#endif // SETUPALGORITHMS_H

