/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_HEADER_H
#define OSGB_MASTER_HEADER_H

#include <iostream>

namespace osg {
    class Header {
    public:
        int high;
        int low;
        int type;//四字节整型，该位置可能为 4 个取值，分别为： 0 代表未知（UNKNOW），
        // 1 代表场景（SCENE）， 2 代表图像（IMAGE）， 3 代表对象（OBJECT），在倾斜摄影数据中，常为 1（SCENE）。
        int version;//倾斜摄影数据所用 osgb 都为 91 版本
        int attribute;//属性位
        int zlibl;//位
        int8_t zlib;//


        int read(std::string &data);


    };
}


#endif //OSGB_MASTER_HEADER_H
