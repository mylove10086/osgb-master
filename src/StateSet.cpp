/**
 *  Created by mylove on 2023/8/12. 
 */

#include "StateSet.h"

using namespace osg;

StateSet::StateSet(int version) {
    this->_version = version;
}

int StateSet::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;


    return index;

}

int StateSet::inheritance(std::string &data, int index) {
    if (_object == NULL) {
        _object = new Object;
    }
    index = _object->contain(data, index);
    return index;
}

int StateSet::contain(std::string &data, int index) {

    memmove(&modeList, &data[index], 1);
    index = index + 1;
    memmove(&attributeList, &data[index], 1);
    index = index + 1;
    if (attributeList == 1) {
        memmove(&attributeNum, &data[index], 4);
        index = index + 4;
        if (attributeNum > 0) {
            for (int i = 0; i < attributeNum; i++) {
                //转到 6.3.14 几何体类osg::Geometry 类
                //固定字段
                int cl;
                memmove(&cl, &data[index], 4);
                index += 4;

                std::string classname;
                classname.resize(cl);
                memmove(&classname[0], &data[index], cl);
                index = index + cl;
                if (classname == "osg::Material") {
                    Material *material = new Material(this->_version);
                    material->classname = "osg::Material";
                    index = material->regular(data, index);
                    index = material->inheritance(data, index);
                    index = material->contain(data, index);
                    _material.push_back(material);
                }
            }
            //这个可能是在上面括号里
            memmove(&materialState, &data[index], 4);
            index = index + 4;

        }
    }
    memmove(&textureModeList, &data[index], 1);
    index = index + 1;
    if (textureModeList == 1) {
        memmove(&textureModeNum, &data[index], 4);
        index = index + 4;
        if (textureModeNum > 0) {
            for (int i = 0; i < textureModeNum; i++) {
                int num;
                memmove(&num, &data[index], 4);
                index = index + 4;
                int text2d;
                memmove(&text2d, &data[index], 4);
                index = index + 4;
                int bit;
                memmove(&bit, &data[index], 4);
                index = index + 4;
                //textureMode.push_back({num, text2d, bit});
            }
        }

    }

    memmove(&textureAttributeList, &data[index], 1);
    index = index + 1;
    if (textureAttributeList == 1) {
        memmove(&textureAttributeNum, &data[index], 4);
        index = index + 4;
        if (textureAttributeNum > 0) {
            memmove(&textureNum, &data[index], 4);
            index = index + 4;
            for (int i = 0; i < textureNum; i++) {
                int cl = 0;
                memmove(&cl, &data[index], 4);
                index += 4;
                std::string classname;
                classname.resize(cl);
                memmove(&classname[0], &data[index], cl);
                index = index + cl;
                if (classname == "osg::Texture2D") {
                    Texture2D *texture2D = new Texture2D(_version);
                    texture2D->classname = "osg::Texture2D";
                    index = texture2D->regular(data, index);
                    index = texture2D->inheritance(data, index);
                    index = texture2D->contain(data, index);
                    _texture.push_back(texture2D);
                }
            }
            //这个可能是在上面括号里
            memmove(&textureState, &data[index], 4);
            index = index + 4;
        }
    }
    memmove(&uniformList, &data[index], 1);
    index = index + 1;
    memmove(&renderingHint, &data[index], 4);
    index = index + 4;
    memmove(&renderBinmode, &data[index], 4);
    index = index + 4;
    memmove(&binNumber, &data[index], 4);
    index = index + 4;
    int strl = 0;
    memmove(&strl, &data[index], 4);
    index = index + 4;
    binName.resize(strl);
    memmove(&binName[0], &data[index], strl);
    index = index + strl;
    memmove(&nestRenderBins, &data[index], 1);
    index = index + 1;
    memmove(&updateCallback, &data[index], 1);
    index = index + 1;
    memmove(&eventCallback, &data[index], 1);
    index = index + 1;
     if(_version>=151){
         // 91版本没有
         memmove(&defineList, &data[index], 1);
         index = index + 1;
     }

    return index;

}

