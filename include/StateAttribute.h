/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_STATEATTRIBUTE_H
#define OSGB_MASTER_STATEATTRIBUTE_H

#include <iostream>

namespace osg {
    class StateAttribute {
    public:

        int _version;

        //更新阶段的回调（UpdateCallback）是否加入到 osgb 的序列化中， osg 中的特有字
        //段，其它引擎不用关注。
        int8_t updateCallback = 0;
        //事件阶段的回调（EventCallback）是否加入到 osgb 的序列化中， osg 中的特有字
        //段，其它引擎不用关注。
        int8_t eventCallback = 0;

        StateAttribute(int);

        int regular(std::string &data, int index);

        /**
         * 包含字段
         * @param data
         * @param index
         * @param ob
         * @return
         */
        int contain(std::string &data, int index);


    };
}


#endif //OSGB_MASTER_STATEATTRIBUTE_H
