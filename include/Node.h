/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_NODE_H
#define OSGB_MASTER_NODE_H

#include <iostream>
#include "Object.h"

namespace osg {
    class Node {
    public:
        int _version;

        int length;
        int identifier = 0;
        std::string classname = "";

        int8_t initialBound;//用户是否设置了初始包围球
        int8_t computeBoundingSphereCallback;//计算包围球的回调
        int8_t updateCallback; //3更新遍历阶段的回调
        int8_t eventCallback;//4事件遍历阶段的回调
        int8_t cullCallback;//5拣选遍历阶段的回调
        int8_t CullingActive;//6节点是否参加了拣选
        //7设置节点掩码
        int nodeMask = 0;
        //8用户是否设置了自定义类型 在 77 之后，移除了这个字段。
        int8_t descriptions;
        //9节点的状态的模式与属性
        int8_t stateSet;

        Object *_object = NULL;

        Node(int version);


        /**
         * 固定字段
         * @param data
         * @param index
         * @return
         */
        int regular(std::string &data, int index);

        /**
         * 继承关系
         * @param data
         * @param index
         * @return
         */
        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index,bool ob=false);

    };
}


#endif //OSGB_MASTER_NODE_H
