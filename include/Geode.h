/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_GEODE_H
#define OSGB_MASTER_GEODE_H

#include <iostream>
#include "Object.h"
#include "Node.h"
#include "Geometry.h"

namespace osg {
    class Geode {
    public:
        bool istateSet = true;//用于参数传递 在group有多个孩子(pagedLod多个)的时候只有第一个孩子的StateSet需要写入基类和包含字段

        int _version = 0;

        //类长度
        int length;
        int identifier;
        std::string classname = "";


        // 1：用户是否自定义了保存渲染数据的类（Drawable）
        int8_t drawable;
        // 写入需要使用渲染数据的文件的个数
        int8_t drawableNum;

        Object *_object = NULL;
        Node *_node = NULL;


        Geometry *geometry = NULL;

        Geode(int version);

        int regular(std::string &data, int index);

        /**
         * 基类的包含字段
         * @param data
         * @param index
         * @return
         */
        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index, bool ob = false);
    };
}


#endif //OSGB_MASTER_GEODE_H
