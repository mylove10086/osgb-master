/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Geode.h"

using namespace osg;

Geode::Geode(int version) {
    this->_version = version;
}

int Geode::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;
    //唯一标识符
    memmove(&identifier, &data[index], 4);
    index = index + 4;

    return index;

}

int Geode::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object;
    }
    if (_node == NULL) {
        _node = new Node(_version);
    }
    index = _object->contain(data, index);
    index = _node->contain(data, index);
    return index;
}

int Geode::contain(std::string &data, int index, bool ob) {

    memmove(&drawable, &data[index], 1);
    index = index + 1;
    memmove(&drawableNum, &data[index], 4);
    index = index + 4;
    if (drawableNum > 0) {
        if (drawableNum > 1) {
            int *it = NULL;
            *it = 1;
        }
        //转到 6.3.14 几何体类osg::Geometry 类
        //固定字段
        int cl;
        memmove(&cl, &data[index], 4);
        index += 4;

        std::string cname;
        cname.resize(cl);
        memmove(&cname[0], &data[index], cl);
        index = index + cl;
        if (cname == "osg::Geometry") {
            geometry = new Geometry(this->_version);
            geometry->istateSet = this->istateSet;
            geometry->classname = "osg::Geometry";
            index = geometry->regular(data, index);
            index = geometry->inheritance(data, index);
            index = geometry->contain(data, index);
        }
    }
    return index;

}

