/**
 *  Created by mylove on 2023/8/15. 
 */

#ifndef OSGB_MASTER_GROUP_H
#define OSGB_MASTER_GROUP_H

#include <iostream>
#include "Object.h"
#include "Node.h"

namespace osg {
    class Group {
    public:
        int _version = 91;

        int length;
        int identifier;
        std::string classname = "";

        // 1： 组内是否有子结点（Children）
        int8_t children = 0;
        int childNum = 0;// 有孩子则孩子的数量就至少为 1，然后开始根据每个孩子的类型逐个读取该数量下的孩子

        Object *_object = NULL;
        Node *_node = NULL;
        StateSet *_stateSet = NULL;//在group有多个孩子(pagedLod多个)的时候只有第一个孩子的StateSet需要写入基类和包含字段
        std::vector<PagedLOD *> pagedLod;
        std::vector<Geode *> geode;



        Group(int version);

        int regular(std::string &data, int index);

        /**
         * 继承关系
         * @param data
         * @param index
         * @return
         */
        int inheritance(std::string &data, int index);

        /**
         * 包含字段
         * @param data
         * @param index
         * @return
         */
        int contain(std::string &data, int index);


    };
}


#endif //OSGB_MASTER_GROUP_H
