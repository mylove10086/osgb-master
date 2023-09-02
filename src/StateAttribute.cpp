/**
 *  Created by mylove on 2023/8/12. 
 */

#include "StateAttribute.h"

using namespace osg;

StateAttribute::StateAttribute(int v) {
    this->_version = v;
}

int StateAttribute::regular(std::string &data, int index) {

}

int StateAttribute::contain(std::string &data, int index) {

    memmove(&updateCallback, &data[index], 1);
    index = index + 1;
    memmove(&eventCallback, &data[index], 1);
    index = index + 1;

    return index;
}


