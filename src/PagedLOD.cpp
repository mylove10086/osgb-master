/**
 *  Created by mylove on 2023/8/12. 
 */

#include "PagedLOD.h"

using namespace osg;

PagedLOD::PagedLOD(int version) {
    this->_version = version;
}

int PagedLOD::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;
    //唯一标识符
    memmove(&identifier, &data[index], 4);
    index = index + 4;

    return index;

}

int PagedLOD::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object;
    }
    if (_node == NULL) {
        _node = new Node(_version);
    }
    if (_lod == NULL) {
        _lod = new LOD(_version);
    }
    index = _object->contain(data, index);
    index = _node->contain(data, index);
    index = _lod->contain(data, index);
    return index;
}

int PagedLOD::contain(std::string &data, int index) {

    memmove(&databasePath, &data[index], 1);
    index = index + 1;
    memmove(&usedatabase, &data[index], 1);
    index = index + 1;
    //memmove(&FrameNumberOfLastTraversal, &data[index], 4);
    //index = index + 4;

    memmove(&numChildrenThatCannotBeExpired, &data[index], 4);
    index = index + 4;

    memmove(&disableExternalChildrenPaging, &data[index], 1);
    index = index + 1;

    memmove(&rangeDataList, &data[index], 1);
    index = index + 1;
    if (rangeDataList == 1) {
        int listnum;
        memmove(&listnum, &data[index], 4);
        index = index + 4;
        if (listnum > 2) {
            int *ints = NULL;
            *ints = 1;
        }

        for (int i = 0; i < listnum; i++) {
            int stl;
            memmove(&stl, &data[index], 4);
            index = index + 4;
            std::string path;
            path.resize(stl);
            memmove(&path[0], &data[index], stl);
            index = index + stl;
            filePath.push_back(path);
        }
        int priority;
        memmove(&priority, &data[index], 4);
        index = index + 4;
        for (int i = 0; i < priority; i++) {
            float prio;
            memmove(&prio, &data[index], 4);
            index = index + 4;
            priorityData.push_back(prio);
            memmove(&prio, &data[index], 4);
            index = index + 4;
            priorityData.push_back(prio);
        }
    }

    memmove(&children, &data[index], 1);
    index = index + 1;
    memmove(&childrenNum, &data[index], 4);
    index = index + 4;
    if (children == 1) {
        for (int i = 0; i < childrenNum; i++) {
            int cl;
            memmove(&cl, &data[index], 4);
            index += 4;
            std::string cname;
            cname.resize(cl);
            memmove(&cname[0], &data[index], cl);
            index = index + cl;
            Geode *g = new Geode(_version);
            g->istateSet = this->istateSet;
            g->classname = "osg::Geode";
            index = g->regular(data, index);
            index = g->inheritance(data, index);
            index = g->contain(data, index);
            geode.push_back(g);
        }
    }
    return index;

}
