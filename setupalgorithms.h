#ifndef SETUPALGORITHMS_H
#define SETUPALGORITHMS_H

#include "toolbox.h"
#include "bruteforce.h"
#include "iteratedSearch.h"
#include "minimumLocalRoute.h"

void setupAlgorithms(std::vector<ToolBox::AlgorithmData> &algorithms){
    {
        ToolBox::AlgorithmData bruteForce;
        bruteForce.name = "Força Bruta";
        bruteForce.run = [](
                GraphicData &g,
                int initialNode,
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = bruteForceSearch(g, initialNode, setSolution, log, chartLog, stopRequested);
            setSolution( s );
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
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {

            Solution s = minimumLocalRoute(g, initialNode, setSolution, log, chartLog, stopRequested);
            setSolution( s );
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
                std::function<void(const Solution&)> setSolution,
                std::function<void(std::string)> log,
                std::function<void(double)> chartLog,
                std::function<bool()> stopRequested,
                std::function<void()> onFinish
            ) -> void {
            Solution s = iteratedSearch(
                        g,    // coordinates
                        2000, // n iterations
                        g.size()*0.2,    // num. of disturbance
                        setSolution, log, chartLog, stopRequested
            );
            setSolution( s );
            onFinish();
        };
        algorithms.emplace_back(iterated);
    }

}

#endif // SETUPALGORITHMS_H

