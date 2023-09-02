/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_LOD_H
#define OSGB_MASTER_LOD_H

#include <iostream>
#include <vector>

namespace osg {
    class LOD {
    public:
        int _version;

        int length;
        int identifier = 0;
        std::string classname = "";

        int centerMode;
        int8_t center; //2 用户是否自定义了中心点
        double shape[4];        //一个三维 double 向量类型和半径 Radius
        int rangeMode;    //3 范围的计算模式
        //4 是否为每个孩子设置最小-最大显示范围
        int8_t rangeList;
        //一个三维 double 向量类型和半径 Radius
        int childnum;

        std::vector<float> minmax;

        LOD(int version);

        int regular(std::string &data, int index);

        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index, bool ob = false);

    };
}


#endif //OSGB_MASTER_LOD_H
