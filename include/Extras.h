/**
 * Created by IBM on 2022/5/13.
 */

#ifndef C_CESIUM_MASTER_EXTRAS_H
#define C_CESIUM_MASTER_EXTRAS_H

#include <iostream>

namespace osg {
    class Pipeline {
    public:
        std::string source = "";
        std::string extension = "";
    };

    class Extras {
    public:
        std::string sourceVersion = "";
        //std::vector<std::string> extensionsUsed;
        bool sourceKHRTechniquesWebGL = false;
        Pipeline *_pipeline = NULL;

        Extras();

        ~Extras();
    };
}


#endif //C_CESIUM_MASTER_EXTRAS_H
