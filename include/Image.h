/**
 *  Created by mylove on 2023/8/13. 
 */

#ifndef OSGB_MASTER_IMAGE_H
#define OSGB_MASTER_IMAGE_H

#include <iostream>
#include <vector>

namespace osg {
    class Image {
    public:
int _version;
        //类长度
        int length;
        int identifier;
        std::string classname = "";

        std::string name = "";

        // 提示文件的来源
        int source = 0;
        // 决定以哪种方式存储
        int storage = 0;
        // storage==1
        u_int size = 0;
        std::vector<unsigned char >data;

        Image(int version);
        int regular(std::string &data, int index);

        int contain(std::string &data, int index);


    };
}


#endif //OSGB_MASTER_IMAGE_H
