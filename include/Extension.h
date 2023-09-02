/**
 * Created by IBM on 2022/5/12.
 */

#ifndef C_CESIUM_MASTER_EXTENSION_H
#define C_CESIUM_MASTER_EXTENSION_H

#include <iostream>
#include <map>
#include <vector>

#include <WebGLConstants.h>
#include "Extras.h"

namespace osg {


    class TechniqueUniform {
    public:
        int count = 0;
        int useInFragment = 0;
        bool node = false;
        bool value = false;
        std::string name = "";
        std::string semantic = "";
        WebGLConstants type;

        TechniqueUniform(std::string name, std::string semantic, WebGLConstants type, int count = 0, int use = 0);

    };

    class Technique {
    public:
        std::map<std::string, TechniqueUniform *> attributes;
        int program;
        std::map<int, TechniqueUniform *> uniforms;

        Technique(std::map<std::string, TechniqueUniform *> &attributes, int program,
                  std::map<int, TechniqueUniform *> &uniforms);
    };


}


#endif //C_CESIUM_MASTER_EXTENSION_H
