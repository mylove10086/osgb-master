/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Drawable.h"

using namespace osg;

Drawable::Drawable(int version) {
    this->_version = version;
}


int Drawable::contain(std::string &data, int index, bool ob) {

    memmove(&stateSet, &data[index], 1);
    index = index + 1;
    if (stateSet == 1) {

        int cl;
        memmove(&cl, &data[index], 4);
        index += 4;

        std::string cname;
        cname.resize(cl);
        memmove(&cname[0], &data[index], cl);
        index = index + cl;
        if (cname == "osg::StateSet") {
            _stateSet = new StateSet(_version);
            _stateSet->classname = "osg::StateSet";
            index = _stateSet->regular(data, index);
            if (this->istateSet) {
                index = _stateSet->inheritance(data, index);
                index = _stateSet->contain(data, index);
            }
        }
    }
    memmove(&initialBound, &data[index], 1);
    index = index + 1;
    memmove(&computeBoundingBoxCallback, &data[index], 1);
    index = index + 1;
    memmove(&shape, &data[index], 1);
    index = index + 1;

    memmove(&displayList, &data[index], 1);
    index = index + 1;
    memmove(&useDisplayList, &data[index], 1);
    index = index + 1;
    memmove(&vertexBufferObjects, &data[index], 1);
    index = index + 1;

    //当使用的 osgb 文件版本在 156 以及 156 以上时（对应的
    //OpenSceneGraph 版本为 3.6.0），移除该字段，不用写入和读取字段。当 osgb 文件版本低于
    if (this->_version < 156) {
        memmove(&updateCallback, &data[index], 1);
        index = index + 1;
        memmove(&eventCallback, &data[index], 1);
        index = index + 1;
        memmove(&cullCallback, &data[index], 1);
        index = index + 1;
        memmove(&drawCallback, &data[index], 1);
        index = index + 1;
    }
    if (this->_version >= 142) {
        //当使用的 OSG 版本高于以及包含 142 时（对应的OpenSceneGraph 版本为 3.5.1），增添该字段，
        // 写入的时候直接写入 0xffffffff 即可， osg中的特有字段，读取的时候其它引擎不用关注。
        memmove(&nodeVisible, &data[index], 1);
        index = index + 1;

    }
    if (this->_version >= 145) {
        memmove(&nodeSelect, &data[index], 1);
        index = index + 1;
    }
    return index;


}
