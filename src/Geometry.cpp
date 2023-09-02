/**
 *  Created by mylove on 2023/8/12. 
 */

#include <VecFormat.h>
#include "Geometry.h"

using namespace osg;

Geometry::Geometry(int version) {
    this->_version = version;
}

int Geometry::regular(std::string &data, int index) {
    //类长度
    //int64_t cl;
    //memmove(&cl, &data[index], 8);
    //index=index+8;

    memmove(&identifier, &data[index], 4);
    index = index + 4;

    return index;

}

int Geometry::inheritance(std::string &data, int index) {
    if (_version <= 155) {
        if (_object == NULL) {
            _object = new Object;
            _drawable = new Drawable(this->_version);
            _drawable->istateSet= this->istateSet;
        }
        index = _object->contain(data, index);
        index = _drawable->contain(data, index);
    } else {
        std::cout << "Geometry::inheritance" << std::endl;
        std::string *str = NULL;
        *str = "";
    }
    return index;
}

int Geometry::contain(std::string &data, int index) {

    memmove(&elements, &data[index], 4);
    index = index + 4;
    memmove(&elementsUint, &data[index], 4);
    index = index + 4;
    memmove(&drawtype, &data[index], 4);
    index = index + 4;
    memmove(&elementnum, &data[index], 4);
    index = index + 4;
    //索引数据
    vertexIndex.resize(elementnum * 4);
    memmove(&vertexIndex[0], &data[index], 4 * elementnum);
    index = index + 4 * elementnum;


    if (this->_version < 112) {
        // 顶点
        memmove(&uvertex, &data[index], 1);
        index = index + 1;
        if (uvertex == 1) {
            memmove(&uvarray, &data[index], 1);
            index = index + 1;
            if (uvarray == 1) {
                memmove(&uvtype, &data[index], 4);
                index = index + 4;
                memmove(&vertextype, &data[index], 4);
                index = index + 4;
                memmove(&vertexnum, &data[index], 4);
                index = index + 4;

                unsigned int length = VecFormat::createTypedArray(vertex, vertextype, vertexnum);
                memmove(&vertex[0], &data[index], length);
                index = index + length;
                memmove(&uvindex, &data[index], 1);
                index = index + 1;
                //当前数据和几何体的绑定方式 04=逐顶点，一般为 04。 02=逐三角面， 1=所有顶点都绑定 1 个值， 0=不绑定
                memmove(&vinway, &data[index], 4);
                index = index + 4;
                memmove(&unitization, &data[index], 4);
                index = index + 4;


            }
        }
        //法线
        memmove(&unormal, &data[index], 1);
        index = index + 1;
        if (unormal == 1) {
            std::string *str = NULL;
            *str = "";
        }
        //颜色
        memmove(&ucolor, &data[index], 1);
        index = index + 1;
        if (ucolor == 1) {
            std::string *str = NULL;
            *str = "";
        }
        //颜色
        memmove(&upcolor, &data[index], 1);
        index = index + 1;
        if (upcolor == 1) {
            std::string *str = NULL;
            *str = "";
        }
        //雾坐标数据
        memmove(&ufog, &data[index], 1);
        index = index + 1;
        if (ufog == 1) {
            std::string *str = NULL;
            *str = "";
        }

        //7用户是否自定义了纹理坐标数据
        memmove(&uvt, &data[index], 1);
        index = index + 1;
        if (uvt == 1) {
            memmove(&vtz, &data[index], 4);
            index = index + 4;
            memmove(&isa, &data[index], 1);
            index = index + 1;
            memmove(&vttype, &data[index], 4);
            index = index + 4;
            memmove(&vtatype, &data[index], 4);
            index = index + 4;
            memmove(&vtanum, &data[index], 4);
            index = index + 4;
            unsigned int length = VecFormat::createTypedArray(vt, vtatype, vtanum);
            memmove(&vt[0], &data[index], length);
            index = index + length;
            memmove(&uvtindex, &data[index], 1);
            index = index + 1;
            memmove(&vtinway, &data[index], 4);
            index = index + 4;
            memmove(&vtnitization, &data[index], 4);
            index = index + 4;
        }

        // 8用户是否自定义了顶点属性数据
        memmove(&vatt, &data[index], 1);
        index = index + 1;
        // 9： 用户是否自定义了快速路径提示，该值为 false 即可，为保兼容性设置的数据
        memmove(&upath, &data[index], 1);
        index = index + 1;

    } else {
        // 10 是否存在顶点数组
        memmove(&existva, &data[index], 1);
        index = index + 1;
        if (existva == 1) {
            int *it = NULL;
            *it = 0;
        }

        //11
        memmove(&unormal, &data[index], 1);
        index = index + 1;
        if (unormal == 1) {
            int *it = NULL;
            *it = 0;
        }
        //12
        memmove(&ucolor, &data[index], 1);
        index = index + 1;
        if (ucolor == 1) {
            int *it = NULL;
            *it = 0;
        }
        //13
        memmove(&upcolor, &data[index], 1);
        index = index + 1;
        if (upcolor == 1) {
            int *it = NULL;
            *it = 0;
        }
        //14 6用户是否自定义了雾坐标数据
        memmove(&ufog, &data[index], 1);
        index = index + 1;
        if (ufog == 1) {
            int *it = NULL;
            *it = 0;
        }
        //15
        memmove(&uvt, &data[index], 1);
        index = index + 1;
        if (uvt == 1) {
            int *it = NULL;
            *it = 0;
        }
        // 16 用户是否自定义了顶点属性数据
        memmove(&vatt, &data[index], 1);
        index = index + 1;
    }
    return index;
}

