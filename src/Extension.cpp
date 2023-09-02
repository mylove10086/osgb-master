/**
 * Created by IBM on 2022/5/12.
 */

#include "Extension.h"

using namespace osg;



TechniqueUniform::TechniqueUniform(std::string name, std::string semantic, WebGLConstants type,
                                   int count, int use) {
    this->name = name;
    this->semantic = semantic;
    this->type = type;
    this->count = count;
    this->useInFragment = use;
}

Technique::Technique(std::map<std::string, TechniqueUniform *> &attributes, int program,
                     std::map<int, TechniqueUniform *> &uniforms) {

    this->attributes.swap(attributes);
    this->uniforms.swap(uniforms);
    this->program = program;
}

