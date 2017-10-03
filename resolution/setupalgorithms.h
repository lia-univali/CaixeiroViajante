#ifndef SETUPALGORITHMS_H
#define SETUPALGORITHMS_H

#include "methods/bruteforce.h"
#include "methods/iteratedSearch.h"
#include "methods/minimumLocalRoute.h"

void setupAlgorithms(std::vector<ToolBox::AlgorithmData> &algorithms){
    { /// BRUTE FORCE
        ToolBox::AlgorithmData bruteForce;
        bruteForce.name = "Força Bruta";
        bruteForce.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<void()>,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = bruteForceSearch(g, initialNode, setSolution, log, chartLog, stopRequested);
            setSolution( s );
            onFinish();
        };
        algorithms.emplace_back(bruteForce);
    }
    { /// CONSTRUCTIVE
        ToolBox::AlgorithmData constructive;
        constructive.name = "Cidade mais Próxima";
        constructive.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<void()>,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {

            Solution s = minimumLocalRoute(g, initialNode, setSolution, log, chartLog, stopRequested);
            setSolution( s );
            onFinish();
        };
        algorithms.emplace_back(constructive);

    }
    { /// ITERATED
        ToolBox::AlgorithmData iterated;
        iterated.name = "Busca Iterada";
        iterated.run = [](
                GraphicData &g,
                int, // initialNode
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<void()>,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = iteratedSearch(
                        g,            // coordinates
                        2000,         // n iterations
                        g.size()*0.05 +1, // num. of disturbance
                        setSolution, log, chartLog, stopRequested
            );
            setSolution( s );
            onFinish();
        };
        algorithms.emplace_back(iterated);
    }
    { /// ITERATED WITH CONSTRUCTIVE
        ToolBox::AlgorithmData iteratedWithConstructive;
        iteratedWithConstructive.name = "Busca Iterada com rota inicial";
        iteratedWithConstructive.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<void()> clearChart,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = minimumLocalRoute(g, initialNode, setSolution, log, chartLog, stopRequested);
            setSolution( s );
            if ( !stopRequested() ){
                clearChart();
                log( "Rota inicial calculada, iniciando busca iterada..." );
                s = iteratedSearch(
                            g,            // coordinates
                            s.path,       // start path
                            2000,         // n iterations
                            g.size()*0.05 +1, // num. of disturbance
                            setSolution, log, chartLog, stopRequested
                );
                setSolution( s );
            }
            onFinish();
        };
        algorithms.emplace_back(iteratedWithConstructive);
    }

}

#endif // SETUPALGORITHMS_H

