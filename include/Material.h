/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_MATERIAL_H
#define OSGB_MASTER_MATERIAL_H

#include <iostream>
#include "Object.h"
#include "StateAttribute.h"


namespace osg {
    class Material {
    public:
        int _version;

        //类长度
        int length;
        int identifier;
        std::string classname = "";


        //表示材质的颜色模式（ColorMode）
        int colorMode = 0x00001603;
        //字段 2：用户是否自定义了环境光（Ambient）
        int8_t ambient = 0;
        int8_t alight = 0;
        float acolor1[4];
        float acolor2[4];
        // 用户是否自定义了漫反射光（Diffuse）
        int8_t diffuse = 0;
        int8_t dlight = 0;
        float dcolor1[4];
        float dcolor2[4];
        // 字段 4：用户是否自定义了镜面光（Specular）
        int8_t specular = 0;
        int8_t slight = 0;
        float scolor1[4];
        float scolor2[4];
        // 用户是否自定义了发射光（Emission）
        int8_t emission = 0;
        int8_t elight = 0;
        float ecolor1[4];
        float ecolor2[4];
        // 用户是否自定义了高光（Shininess）
        int8_t shininess = 0;
        int8_t shlight = 0;
        float shcolor1;
        float shcolor2;


        Object *_object=NULL;
        StateAttribute *_stateAttribute=NULL;

        Material(int version);


        int regular(std::string &data, int index);

        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index, bool ob = false);


    };
}


#endif //OSGB_MASTER_MATERIAL_H
