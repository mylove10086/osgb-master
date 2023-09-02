/**
 *  Created by mylove on 2023/8/13. 
 */

#include "Texture.h"

using namespace osg;

Texture::Texture(int ve) {
    this->_version = ve;
}

int Texture::regular(std::string &data, int index) {

}

int Texture::baseCon(std::string &data, int index) {

}

int Texture::contain(std::string &data, int index) {

    memmove(&WRAP_S, &data[index], 1);
    index = index + 1;
    memmove(&xModel, &data[index], 4);
    index = index + 4;
    memmove(&WRAP_T, &data[index], 1);
    index = index + 1;
    memmove(&tModel, &data[index], 4);
    index = index + 4;
    memmove(&WRAP_R, &data[index], 1);
    index = index + 1;
    memmove(&rModel, &data[index], 4);
    index = index + 4;
    memmove(&min_filter, &data[index], 1);
    index = index + 1;
    memmove(&mlinear, &data[index], 4);
    index = index + 4;
    memmove(&mag_filter, &data[index], 1);
    index = index + 1;
    memmove(&alinear, &data[index], 4);
    index = index + 4;
    memmove(&maxAnisotropy, &data[index], 4);
    index = index + 4;
    memmove(&mipmap, &data[index], 1);
    index = index + 1;
    memmove(&unRefImageDataAfterApply, &data[index], 1);
    index = index + 1;
    memmove(&clientStorageHint, &data[index], 1);
    index = index + 1;
    memmove(&resizeNonPowerOfTwoHint, &data[index], 1);
    index = index + 1;
    memmove(&borderColor[0], &data[index], 32);
    index = index + 32;
    memmove(&borderWidth, &data[index], 4);
    index = index + 4;
    memmove(&internalFormatMode, &data[index], 4);
    index = index + 4;
    memmove(&USE_USER_DEFINED_FORMAT, &data[index], 1);
    index = index + 1;
    memmove(&sourceFormat, &data[index], 1);
    index = index + 1;
    memmove(&sourceType, &data[index], 1);
    index = index + 1;
    memmove(&GL_TEXTURE_COMPARE_MODE_ARB, &data[index], 1);
    index = index + 1;
    memmove(&shadowCompareFunc, &data[index], 4);
    index = index + 4;
    memmove(&shadowTextureMode, &data[index], 4);
    index = index + 4;
    memmove(&shadowAmbient, &data[index], 4);
    index = index + 4;
    if(this->_version>91){
        // 161版本，osgb 版本为 91，所以后面的五个字段都无需读取
        memmove(&imageAttachment, &data[index], 1);
        index = index + 1;
        memmove(&swizzle, &data[index], 1);
        index = index + 1;
        memmove(&minLOD, &data[index], 4);
        index = index + 4;
        memmove(&maxLOD, &data[index], 4);
        index = index + 4;
        memmove(&LODBias, &data[index], 4);
        index = index + 4;
    }
    return index;
}

