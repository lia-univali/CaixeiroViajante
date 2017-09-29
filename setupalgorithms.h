#ifndef SETUPALGORITHMS_H
#define SETUPALGORITHMS_H

#include "toolbox.h"

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
            while ( !stopRequested() && i < 800 ){
                double y = (double) rand() - RAND_MAX/2.;
                chartLog( y );
                log( "["+std::to_string(i) +"]:  "+ std::to_string(y) );
                ++i;
                std::this_thread::sleep_for( std::chrono::milliseconds(20) );
            }
            onFinish();
        };
        algorithms.emplace_back(test);
    }

}

#endif // SETUPALGORITHMS_H

