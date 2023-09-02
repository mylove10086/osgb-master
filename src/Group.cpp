/**
 *  Created by mylove on 2023/8/15. 
 */

#include <PagedLOD.h>
#include <Geode.h>
#include "Group.h"

using namespace osg;

Group::Group(int version) {
    this->_version = version;
}


int Group::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;
    //唯一标识符
    memmove(&identifier, &data[index], 4);
    index = index + 4;

    return index;
}

int Group::inheritance(std::string &data, int index) {

    if (_object == NULL) {
        _object = new Object();
    }
    if (_node == NULL) {
        _node = new Node(_version);
    }
    index = _object->contain(data, index);
    index = _node->contain(data, index);
    return index;
}

int Group::contain(std::string &data, int index) {

    memmove(&children, &data[index], 1);
    index = index + 1;
    memmove(&childNum, &data[index], 4);
    index = index + 4;
    for (int i = 0; i < childNum; i++) {
        int stl = 0;
        memmove(&stl, &data[index], 4);
        index = index + 4;
        std::string cname;
        cname.resize(stl);
        memmove(&cname[0], &data[index], stl);
        index = index + stl;

        if (cname == "osg::PagedLOD") {
            PagedLOD *p = new PagedLOD(this->_version);
            p->istateSet = this->_stateSet == NULL ? true : false;
            p->classname = "osg::PagedLOD";
            index = p->regular(data, index);
            index = p->inheritance(data, index);
            index = p->contain(data, index);
            if (this->_stateSet == NULL) {
                int le = p->geode.size();
                for (int j = 0; j < le; j++) {
                    Geode *g = p->geode[j];
                    this->_stateSet = g->geometry->_drawable->_stateSet;
                    if (this->_stateSet != NULL) {
                        break;
                    }
                }
            }
            pagedLod.push_back(p);
        } else if (cname == "osg::Geode") {
            Geode *g = new Geode(this->_version);
            g->classname = "osg::Geode";
            index = g->regular(data, index);
            index = g->inheritance(data, index);
            index = g->contain(data, index);
            geode.push_back(g);
        } else {
            int *tt = NULL;
            *tt = 1;
        }


    }


    return index;

}
