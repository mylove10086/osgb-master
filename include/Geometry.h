/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_GEOMETRY_H
#define OSGB_MASTER_GEOMETRY_H

#include <iostream>
#include "Object.h"
#include "Drawable.h"

namespace osg {
    class Geometry {
    public:
        bool istateSet = true;//用于参数传递 在group有多个孩子(pagedLod多个)的时候只有第一个孩子的StateSet需要写入基类和包含字段

        int _version = 0;

        // 固定字段
        //类长度
        int length = 0;
        //唯一标识符
        int identifier;
        std::string classname = "";

        // 定义有多少个片元集合，以及每个片元集合中的索引和连接方式等
        int elements = 0;
        int elementsUint;//确定片元中存放的索引的类型
        int drawtype;//索引连接的方式
        int elementnum;//代素表索引中的元数量
        std::vector<unsigned char> vertexIndex;

        //版本112以下
        // 2用户是否定义了顶点数据。
        int8_t uvertex = 0;//表示存在顶点数据
        int8_t uvarray = 0;//有没有数组
        int uvtype = 0;//数组标识符
        int vertextype = 0;//数组中元素的类型
        int vertexnum = 0;//顶点的数量
        std::vector<unsigned char> vertex;
        int8_t uvindex = 0;//代表有没有索引数据
        int vinway;//当前数据和几何体的绑定方式 04=逐顶点，一般为 04。 02=逐三角面， 1=所有顶点都绑定 1 个值， 0=不绑定
        int unitization;//否要来对当前顶点单位化

        //3 用户是否自定义了法线数组
        int8_t unormal = 0;
        // 4用户是否自定义了颜色数据
        int8_t ucolor = 0;

        // 5用户是否自定义了辅助颜色数据
        int8_t upcolor = 0;

        // 6用户是否自定义了雾坐标数据
        int8_t ufog = 0;

        // 7用户是否自定义了纹理坐标数据
        int8_t uvt = 0;
        int vtz = 0;//有几组纹理坐标
        int8_t isa = 0;//代表是否有数组
        int vttype = 0;//数组的标识符
        int vtatype = 0;//代表数组类型
        int vtanum = 0;//数组的长度
        std::vector<unsigned char> vt;
        int8_t uvtindex = 0; //代表有没有索引数据
        // 代表当前数据和几何体的绑
        int vtinway;//定方式 04=逐顶点，一般为 04。 02=逐三角面， 1=所有顶点都绑定 1 个值， 0 =不绑定
        int vtnitization;//是否要来对当前顶点单位化

        // 8： 用户是否自定义了顶点属性数据
        int8_t vatt = 0; //代表有没有索引数据
        // 9： 用户是否自定义了快速路径提示，该值为 false 即可，为保兼容性设置的数据
        int8_t upath = 0; //代表有没有索引数据

        //版本112以上

        // 10 是否存在顶点数组
        int8_t existva = 0;


        Object *_object;
        Drawable *_drawable;

        Geometry(int);

        int regular(std::string &data, int index);

        /**
         * 基类的包含字段
         * @param data
         * @param index
         * @return
         */
        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index);

    };
}


#endif //OSGB_MASTER_GEOMETRY_H
