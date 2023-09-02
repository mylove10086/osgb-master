/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Object.h"

using namespace osg;

int Object::regular(std::string &data, int index) {

}

int Object::contain(std::string &data, int index,bool ob) {
    int ol;
    memmove(&ol, &data[index], 4);
    index = index + 4;
    //无名称 名称（Name），给类代表的内容命名。
    name.resize(ol);
    memmove(&name[0], &data[index], ol);
    index = index + ol;

    memmove(&dataVariance, &data[index], 4);
    index = index + 4;
    memmove(&userData, &data[index], 1);
    index = index + 1;
    return index;
}