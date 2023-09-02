/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Material.h"

using namespace osg;

Material::Material(int version) {
    this->_version = version;
}

int Material::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;


    return index;
}

int Material::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object;
    }if (_stateAttribute == NULL) {
        _stateAttribute = new StateAttribute(this->_version);
    }
    index = _object->contain(data, index);
    index = _stateAttribute->contain(data, index);

    return index;
}

int Material::contain(std::string &data, int index, bool ob) {

    memmove(&colorMode, &data[index], 4);
    index = index + 4;

    memmove(&ambient, &data[index], 1);
    index = index + 1;
    if (ambient == 1) {
        memmove(&alight, &data[index], 1);
        index = index + 1;
        if (alight == 1) {
            memmove(&acolor1[0], &data[index], 4 * 4);
            index = index + 4 * 4;
            memmove(&acolor2[0], &data[index], 4 * 4);
            index = index + 4 * 4;
        }
    }
    memmove(&diffuse, &data[index], 1);
    index = index + 1;
    if (diffuse == 1) {
        memmove(&dlight, &data[index], 1);
        index = index + 1;
        if (dlight == 1) {
            memmove(&dcolor1[0], &data[index], 4 * 4);
            index = index + 4 * 4;
            memmove(&dcolor2[0], &data[index], 4 * 4);
            index = index + 4 * 4;
        }
    }
    memmove(&specular, &data[index], 1);
    index = index + 1;
    if (specular == 1) {
        memmove(&slight, &data[index], 1);
        index = index + 1;
        if (slight == 1) {
            memmove(&scolor1[0], &data[index], 4 * 4);
            index = index + 4 * 4;
            memmove(&scolor2[0], &data[index], 4 * 4);
            index = index + 4 * 4;
        }
    }
    memmove(&emission, &data[index], 1);
    index = index + 1;
    if (emission == 1) {
        memmove(&elight, &data[index], 1);
        index = index + 1;
        if (elight == 1) {
            memmove(&ecolor1[0], &data[index], 4 * 4);
            index = index + 4 * 4;
            memmove(&ecolor2[0], &data[index], 4 * 4);
            index = index + 4 * 4;
        }
    }
    memmove(&shininess, &data[index], 1);
    index = index + 1;
    if (shininess == 1) {
        memmove(&shlight, &data[index], 1);
        index = index + 1;
        if (shlight == 1) {
            memmove(&shcolor1, &data[index], 4);
            index = index + 4;
            memmove(&shcolor2, &data[index], 4);
            index = index + 4;
        }
    }
    return index;
}