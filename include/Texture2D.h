/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_TEXTURE2D_H
#define OSGB_MASTER_TEXTURE2D_H

#include <iostream>
#include "Object.h"
#include "Image.h"
#include "StateAttribute.h"
#include "Texture.h"

namespace osg {
    class Texture2D {
    public:
        int _version;
        //类长度
        int length;
        int identifier;
        std::string classname = "";

        // 是否可以获得纹理图像
        int8_t isImage = 0;
        // 纹理的宽度（TextureWidth）
        float textureWidth = 0;
        // 纹理的高度（TextureHeight）
        float textureHeight = 0;


        Object *_object=NULL;
        Object *_objecttl=NULL;//红色线条部分是 6.3.3 对象类 osg::Object 的包含字段的序列化。（特例）。
        StateAttribute *_stateAttribute= NULL;
        Texture *_texture= NULL;
        Image *_image = NULL;

        Texture2D(int);
        int regular(std::string &data, int index);

        int inheritance(std::string &data, int index);
        int contain(std::string &data, int index);


    };
}


#endif //OSGB_MASTER_TEXTURE2D_H
