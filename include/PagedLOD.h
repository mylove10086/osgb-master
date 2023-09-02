/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_PAGEDLOD_H
#define OSGB_MASTER_PAGEDLOD_H

#include <iostream>
#include "Object.h"
#include "Node.h"
#include "LOD.h"
#include "Geode.h"

namespace osg {
    class PagedLOD {
    public:
        bool istateSet = true;//用于参数传递 在group有多个孩子(pagedLod多个)的时候只有第一个孩子的StateSet需要写入基类和包含字段

        int _version = 91;

        int length;
        int identifier;
        std::string classname = "";

        //1 用户是否自定义了数据库路径
        int8_t databasePath;
        int8_t usedatabase;
        //2 最后一次遍历的帧数,移除了这个字在 osgb 文件版本为 70 的时候6 文件体
        //（对应最接近的 osg 正式版本为 2.9.11）发生过一次变化，在 70 之后，移除了这个字段
        int frameNumberOfLastTraversal;
        //3 必须保留的子节点数量
        int numChildrenThatCannotBeExpired;
        //4 禁用从磁盘加载节点
        int8_t disableExternalChildrenPaging;
        // 5：用户是否自定义了文件列表
        int8_t rangeDataList;
        std::vector<std::string> filePath;
        std::vector<float> priorityData;
        // 6：是否可以获得从外部加载的文件（Children）
        int8_t children;
        int childrenNum;
        std::vector<Geode *> geode;

        Object *_object = NULL;
        Node *_node = NULL;
        LOD *_lod = NULL;

        PagedLOD(int version);

        int regular(std::string &data, int index);

        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index);

    };
}


#endif //OSGB_MASTER_PAGEDLOD_H
