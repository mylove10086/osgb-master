/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Node.h"

using namespace osg;

Node::Node(int version) {
    this->_version = version;
}

int Node::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;

    return index;
}

int Node::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object();
    }

    index = _object->contain(data, index);
    return index;
}


int Node::contain(std::string &data, int index, bool ob) {
    memmove(&initialBound, &data[index], 1);
    index = index + 1;
    memmove(&computeBoundingSphereCallback, &data[index], 1);
    index = index + 1;
    memmove(&updateCallback, &data[index], 1);
    index = index + 1;
    memmove(&eventCallback, &data[index], 1);
    index = index + 1;
    memmove(&cullCallback, &data[index], 1);
    index = index + 1;
    memmove(&CullingActive, &data[index], 1);
    index = index + 1;
    memmove(&nodeMask, &data[index], 4);
    index = index + 4;
    //memmove(&descriptions, &data[index], 1);
    //index = index + 1;
    memmove(&stateSet, &data[index], 1);
    index = index + 1;
    // 如果StateSet是1，则读StateSet类读字段
    if (stateSet == 1) {
        std::cout << "stateSet" << std::endl;
        std::string *str = NULL;
        *str = ";";
    }


    return index;
}

