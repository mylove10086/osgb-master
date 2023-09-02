/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_OBJECT_H
#define OSGB_MASTER_OBJECT_H

#include <iostream>

namespace osg {
    class Object {
    public:
        int dataVariance;//数据是否是动态的
        int8_t userData;//用户自定义数据

        std::string name = "";

        int regular(std::string &data, int index);

        int contain(std::string &data, int index,bool ob=false);

    };
}


#endif //OSGB_MASTER_OBJECT_H
