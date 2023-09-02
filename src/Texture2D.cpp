/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Texture2D.h"

using namespace osg;

Texture2D::Texture2D(int ver) {
    this->_version = ver;

}

int Texture2D::regular(std::string &data, int index) {
//类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;


    return index;
}

int Texture2D::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object;
    }
    if (_stateAttribute == NULL) {
        _stateAttribute = new StateAttribute(_version);
    }
    if (_texture == NULL) {
        _texture = new Texture(_version);
    }
    index = _object->contain(data, index);
    index = _stateAttribute->contain(data, index);
    index = _texture->contain(data, index);
    return index;
}

int Texture2D::contain(std::string &data, int index) {
    memmove(&isImage, &data[index], 1);
    index = index + 1;
    if (isImage == 1) {
        _image = new Image(_version);
        _image->classname = "osg::Image";
        index = _image->regular(data, index);
        index = _image->contain(data, index);
        if (_objecttl == NULL) {
            _objecttl = new Object();
        }
        index = _objecttl->contain(data, index);
    }

    memmove(&textureWidth, &data[index], 4);
    index = index + 4;
    memmove(&textureHeight, &data[index], 4);
    index = index + 4;


    return index;
}

