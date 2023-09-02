/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_DRAWABLE_H
#define OSGB_MASTER_DRAWABLE_H

#include <iostream>
#include "Object.h"
#include "StateSet.h"

namespace osg {
    class Drawable {
    public:

        bool istateSet = true;//用于参数传递 在group有多个孩子(pagedLod多个)的时候只有第一个孩子的StateSet需要写入基类和包含字段

        int _version = 91;

        // 固定字段
        //类长度
        int length = 0;
        //唯一标识符
        int identifier;
        std::string classname = "";

        // 是否设置了状态 当使用的 osgb 文件版本在 156 以及 156 以上时（对应的 OpenSceneGraph
        //版本为 3.6.0），移除字段 1 和字段 8~11，共五个字段； osgb 文件版本低于 156 时，保留该
        //部分字段
        int8_t stateSet = 0;
        //表示 InitialBound（初始包围球）是否给定 倾斜摄影默认情况下文件中是不存
        //的，因此这里也是固定 0
        int8_t initialBound = 0;
        // 是否指定了计算包围球的 callback
        int8_t computeBoundingBoxCallback = 0;
        //表示内置几何体 Shape 是否参与到序列化中
        int8_t shape = 0;
        //表示是否支持 DisplayList
        int8_t displayList = 1;
        //表示是否使用 DisplayList
        int8_t useDisplayList = 1;
        //表示是否使用 VertexBufferObjects
        int8_t vertexBufferObjects = 0;
        //表示是否将 UpdateCallback 参与进序列化中,非关键字段。 当使用的 osgb 文件版本在 156 以及 156 以上时（对应的
        //OpenSceneGraph 版本为 3.6.0），移除该字段，不用写入和读取字段。当 osgb 文件版本低于
        //156，写入的时候直接写入 0 即可， osg 中的特有字段，读取的时候其它引擎不用关注。
        int8_t updateCallback = 0;
        // 表示是否将 EventCallback 参与进序列化中.非关键字段。 当使用的 osgb 文件版本在 156 以及 156 以上时（对应的
        //OpenSceneGraph 版本为 3.6.0），移除该字段，不用写入和读取字段。当 osgb 文件版本低于
        //156，写入的时候直接写入 0 即可， osg 中的特有字段，读取的时候其它引擎不用关注。
        int8_t eventCallback = 0;

        //表示是否将 CullCallback 参与进序列化中.当使用的 osgb 文件版本在 156 以及 156 以上时（对应的
        //OpenSceneGraph 版本为 3.6.0），移除该字段，不用写入和读取字段。当 osgb 文件版本低于
        //156，写入的时候直接写入 0 即可， osg 中的特有字段，读取的时候其它引擎不用关注
        int8_t cullCallback = 0;
        //表示是否将 DrawCallback 参与进序列化中。当使用的 osgb 文件版本在 156 以及 156 以上时（对应的
        //OpenSceneGraph 版本为 3.6.0），移除该字段，不用写入和读取字段。当 osgb 文件版本低于
        //156，写入的时候直接写入 0 即可， osg 中的特有字段，读取的时候其它引擎不用关注
        int8_t drawCallback = 0;

        // 表示结点显隐,当使用的 OSG 版本高于以及包含 142 时（对应的
        //OpenSceneGraph 版本为 3.5.1），增添该字段，写入的时候直接写入 0xffffffff 即可， osg
        //中的特有字段，读取的时候其它引擎不用关注。
        int nodeVisible = 0xffffffff;
        //表示结点是否参加拣选，默认值为 1,默认参加。 不参加拣选的结点不会显示在场景中
        //非关键字段，当使用的 osgb 文件版本在 145 以及 145 以上时（对应的
        //OpenSceneGraph 版本为 3.5.4），增添该字段。写入的时候直接写入 0x01 即可， osg 中的特
        //有字段，读取的时候其它引擎不用关注。
        int nodeSelect = 1;


        Object _object;
        StateSet *_stateSet = NULL;

        Drawable(int version);

        int contain(std::string &data, int index, bool ob = false);


    };
}


#endif //OSGB_MASTER_DRAWABLE_H
