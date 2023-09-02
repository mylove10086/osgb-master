/**
 *  Created by mylove on 2023/8/13. 
 */

#include "Image.h"

using namespace osg;

Image::Image(int version) {
    this->_version = version;
}

int Image::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;
    return index;
}

int Image::contain(std::string &data, int index) {

    int le = 0;
    memmove(&le, &data[index], 4);
    index = index + 4;
    name.resize(le);
    memmove(&name[0], &data[index], le);
    index = index + le;
    memmove(&source, &data[index], 4);
    index = index + 4;
    memmove(&storage, &data[index], 4);
    index = index + 4;
    switch (storage) {
        case 1:
            memmove(&size, &data[index], 4);
            index = index + 4;
            this->data.resize(size);
            memmove(&this->data[0], &data[index], size);
            index = index + size;
            break;
        case 2://文件是外部的

            break;

    }
    return index;
}


