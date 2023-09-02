/**
 *  Created by mylove on 2023/8/12. 
 */

#include "LOD.h"

using namespace osg;

LOD::LOD(int version) {
    this->_version = version;
}


int LOD::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;
    return index;

}
int LOD::inheritance(std::string &data, int index) {


    return index;
}


int LOD::contain(std::string &data, int index, bool ob) {
    memmove(&centerMode, &data[index], 4);
    index = index + 4;
    //2 用户是否自定义了中心点
    memmove(&center, &data[index], 1);
    index = index + 1;
    if (center == 1) {
        memmove(&shape[0], &data[index], 32);
        index = index + 32;
    }
    memmove(&rangeMode, &data[index], 4);
    index = index + 4;

    memmove(&rangeList, &data[index], 1);
    index = index + 1;
    if (rangeList == 1) {

        memmove(&childnum, &data[index], 4);
        index = index + 4;
        //最小-最大显示范围
        minmax.resize(childnum * 2);
        memmove(&minmax[0], &data[index], childnum * 2 * 4);
        index = index + childnum * 2 * 4;

    }

    return index;
}

