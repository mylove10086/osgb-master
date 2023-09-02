#include <iostream>
#include <fstream>
#include <vector>
#include <Geometry.h>
#include "Drawable.h"

using namespace osg;

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string fileurl = "../data/1536.terrain";
    fileurl = "../data/Tile_+008_+013_L21_0003300.osgb";
    fileurl = "../data/Tile_11_L24_00100000.osgb";
    std::ifstream ifstream;
    std::string json = "";
    ifstream.open(fileurl, std::ios::in);
    if (ifstream.is_open()) {
        json.append((std::istreambuf_iterator<char>(ifstream)), std::istreambuf_iterator<char>());
        ifstream.close();
    }
    std::cout << json.size() << std::endl;
    int closs1;
    memmove(&closs1, &json[25], 4);

    std::string classname;
    classname.resize(closs1);
    memmove(&classname[0], &json[29], closs1);
    int pos = 29 + closs1;

    //类长度
    //int64_t cl;
    //memmove(&cl, &json[pos], 8);
    //pos=pos+8;
    //唯一标识符
    int one;
    memmove(&one, &json[pos], 4);
    pos = pos + 4;

    // 包含字段,osg::PagedLOD类继承自osg::PagedLOD 继承自类 osg::LOD, 而 osg::LOD 的父类是 osg::Node，
    //osg::Node 的父类是 osg::Object，先读object的包含字段

    //结点类 osg::Object
    //长度-值
    int ol;
    memmove(&ol, &json[pos], 4);
    pos = pos + 4;
    //无名称 名称（Name），给类代表的内容命名。
    std::string oname;
    oname.resize(ol);
    memmove(&oname[0], &json[pos], ol);
    pos = pos + ol;
    //数据是否是动态的
    int DataVariance;
    memmove(&DataVariance, &json[pos], 4);
    pos = pos + 4;

    //用户自定义数据
    int8_t UserData;
    memmove(&UserData, &json[pos], 1);
    pos = pos + 1;

    //结点类 osg::Node
    // osg::Node 是场景图形中所有节点的基类，继承自 osg::Object 类，一般不在序列化中单
    // 独出现。 它的子类包括了用于实现动态分页加载的类以及用于进行状态设置与渲染的类等
    //1用户是否设置了初始包围球
    int8_t initialBound;
    memmove(&initialBound, &json[pos], 1);
    pos = pos + 1;
    //2计算包围球的回调
    int8_t computeBoundingSphereCallback;
    memmove(&computeBoundingSphereCallback, &json[pos], 1);
    pos = pos + 1;
    //3更新遍历阶段的回调
    int8_t updateCallback;
    memmove(&updateCallback, &json[pos], 1);
    pos = pos + 1;
    //4事件遍历阶段的回调
    int8_t eventCallback;
    memmove(&eventCallback, &json[pos], 1);
    pos = pos + 1;
    //5拣选遍历阶段的回调
    int8_t cullCallback;
    memmove(&cullCallback, &json[pos], 1);
    pos = pos + 1;
    //6节点是否参加了拣选
    int8_t CullingActive;
    memmove(&CullingActive, &json[pos], 1);
    pos = pos + 1;
    //7设置节点掩码
    int NodeMask = 0;
    memmove(&NodeMask, &json[pos], 4);
    pos = pos + 4;
    //8用户是否设置了自定义类型 在 77 之后，移除了这个字段。
    //int8_t Descriptions;
    //memmove(&Descriptions, &json[pos], 1);
    //pos = pos + 1;
    //9节点的状态的模式与属性
    int8_t StateSet;
    memmove(&StateSet, &json[pos], 1);
    pos = pos + 1;
    // 如果StateSet是1，则读StateSet类读字段




    // osg::LOD
    //1 对象的中心点的模式
    int CenterMode;
    memmove(&CenterMode, &json[pos], 4);
    pos = pos + 4;
    //2 用户是否自定义了中心点
    int8_t Center;
    memmove(&Center, &json[pos], 1);
    pos = pos + 1;
    if (Center == 1) {
        //一个三维 double 向量类型和半径 Radius
        double vec[4];
        memmove(&vec[0], &json[pos], 32);
        pos = pos + 32;
    }
    //3 范围的计算模式
    int RangeMode;
    memmove(&RangeMode, &json[pos], 4);
    pos = pos + 4;
    //4 是否为每个孩子设置最小-最大显示范围
    int8_t RangeList;
    memmove(&RangeList, &json[pos], 1);
    pos = pos + 1;
    if (RangeList == 1) {
        //一个三维 double 向量类型和半径 Radius
        int childcount;
        memmove(&childcount, &json[pos], 4);
        pos = pos + 4;
        //最小-最大显示范围
        float vec1[2 * 2];
        memmove(&vec1[0], &json[pos], childcount * 2 * 4);
        pos = pos + childcount * 2 * 4;

    }

    //分页数据类 osg::PagedLOD

    //1 用户是否自定义了数据库路径
    int8_t DatabasePath;
    memmove(&DatabasePath, &json[pos], 1);
    pos = pos + 1;
    int8_t DatabasePath1;
    memmove(&DatabasePath1, &json[pos], 1);
    pos = pos + 1;
    //2 最后一次遍历的帧数,移除了这个字
    //int FrameNumberOfLastTraversal;
    //memmove(&FrameNumberOfLastTraversal, &json[pos], 4);
    //pos = pos + 4;
    //3 必须保留的子节点数量
    int PagedLOD;
    memmove(&PagedLOD, &json[pos], 4);
    pos = pos + 4;
    //4 禁用从磁盘加载节点
    int8_t DisableExternalChildrenPaging;
    memmove(&DisableExternalChildrenPaging, &json[pos], 1);
    pos = pos + 1;
    // 5：用户是否自定义了文件列表
    int8_t RangeDataList;
    memmove(&RangeDataList, &json[pos], 1);
    pos = pos + 1;
    if (RangeDataList == 1) {
        int Listcount;
        memmove(&Listcount, &json[pos], 4);
        pos = pos + 4;

        std::vector<std::string> filepath;
        for (int i = 0; i < Listcount; i++) {
            int stl;
            memmove(&stl, &json[pos], 4);
            pos = pos + 4;
            std::string path;
            path.resize(stl);
            memmove(&path[0], &json[pos], stl);
            pos = pos + stl;
            filepath.push_back(path);
            std::cout << path << std::endl;
        }
        int priority;
        memmove(&priority, &json[pos], 4);
        pos = pos + 4;
        std::vector<float> prioritydata;
        for (int i = 0; i < priority; i++) {
            float prio;
            memmove(&prio, &json[pos], 4);
            pos = pos + 4;
            prioritydata.push_back(prio);
            memmove(&prio, &json[pos], 4);
            pos = pos + 4;
            prioritydata.push_back(prio);
        }
    }
    // 6：是否可以获得从外部加载的文件（Children）
    int8_t Children;
    memmove(&Children, &json[pos], 1);
    pos = pos + 1;
    int Childrennum;
    memmove(&Childrennum, &json[pos], 4);
    pos = pos + 4;
    //if(Childrennum>1){
    //几何结点类 osg::Geode 类
    //}

    // 几何结点类 osg::Geode 类
    int gcl;
    memmove(&gcl, &json[pos], 4);
    pos = pos + 4;
    //无名称 名称（Name），给类代表的内容命名。
    std::string gname;
    gname.resize(gcl);
    memmove(&gname[0], &json[pos], gcl);
    pos = pos + gcl;

    //类长度
    //int64_t cl;
    //memmove(&cl, &json[pos], 8);
    //pos=pos+8;
    //唯一标识符
    int gone;
    memmove(&gone, &json[pos], 4);
    pos = pos + 4;

    //结点类 osg::Object
    //长度-值
    int ol1;
    memmove(&ol1, &json[pos], 4);
    pos = pos + 4;
    //无名称 名称（Name），给类代表的内容命名。
    std::string oname1;
    oname.resize(ol1);
    memmove(&oname1[0], &json[pos], ol);
    pos = pos + ol;
    //数据是否是动态的
    int DataVariance1;
    memmove(&DataVariance1, &json[pos], 4);
    pos = pos + 4;

    //用户自定义数据
    int8_t UserData1;
    memmove(&UserData1, &json[pos], 1);
    pos = pos + 1;

    //结点类 osg::Node
    // osg::Node 是场景图形中所有节点的基类，继承自 osg::Object 类，一般不在序列化中单
    // 独出现。 它的子类包括了用于实现动态分页加载的类以及用于进行状态设置与渲染的类等
    //1用户是否设置了初始包围球
    int8_t initialBound1;
    memmove(&initialBound1, &json[pos], 1);
    pos = pos + 1;
    //2计算包围球的回调
    int8_t computeBoundingSphereCallback1;
    memmove(&computeBoundingSphereCallback1, &json[pos], 1);
    pos = pos + 1;
    //3更新遍历阶段的回调
    int8_t updateCallback1;
    memmove(&updateCallback1, &json[pos], 1);
    pos = pos + 1;
    //4事件遍历阶段的回调
    int8_t eventCallback1;
    memmove(&eventCallback1, &json[pos], 1);
    pos = pos + 1;
    //5拣选遍历阶段的回调
    int8_t cullCallback1;
    memmove(&cullCallback1, &json[pos], 1);
    pos = pos + 1;
    //6节点是否参加了拣选
    int8_t CullingActive1;
    memmove(&CullingActive1, &json[pos], 1);
    pos = pos + 1;
    //7设置节点掩码
    int NodeMask1 = 0;
    memmove(&NodeMask1, &json[pos], 4);
    pos = pos + 4;
    //8用户是否设置了自定义类型 在 77 之后，移除了这个字段。
    //int8_t Descriptions;
    //memmove(&Descriptions, &json[pos], 1);
    //pos = pos + 1;
    //9节点的状态的模式与属性
    int8_t StateSet1;
    memmove(&StateSet1, &json[pos], 1);
    pos = pos + 1;
    // 如果StateSet是1，则读StateSet类读字段


    // geode包含字段
    // 1：用户是否自定义了保存渲染数据的类（Drawable）
    int8_t Drawable0;
    memmove(&Drawable0, &json[pos], 1);
    pos = pos + 1;
    // 写入需要使用渲染数据的文件的个数
    int8_t Drawablenum;
    memmove(&Drawablenum, &json[pos], 4);
    pos = pos + 4;
    if (Drawablenum > 0) {
        //转到 6.3.14 几何体类osg::Geometry 类

        //结点类 osg::Object
        //长度-值
        memmove(&ol1, &json[pos], 4);
        pos = pos + 4;

        //无名称 名称（Name），给类代表的内容命名。
        std::string oname1;
        oname1.resize(ol1);
        memmove(&oname1[0], &json[pos], ol1);
        pos = pos + ol1;

        //类长度
        //int64_t cl;
        //memmove(&cl, &data[index], 8);
        //index=index+8;
        int identifier;
        memmove(&identifier, &json[pos], 4);
        pos = pos + 4;

        //长度-值
        int ol;
        memmove(&ol, &json[pos], 4);
        pos = pos + 4;
        //无名称 名称（Name），给类代表的内容命名。
        std::string oname;
        oname.resize(ol);
        memmove(&oname[0], &json[pos], ol);
        pos = pos + ol;
        //数据是否是动态的
        int DataVariance;
        memmove(&DataVariance, &json[pos], 4);
        pos = pos + 4;

        //用户自定义数据
        int8_t UserData;
        memmove(&UserData, &json[pos], 1);
        pos = pos + 1;

        // Drawable





    }


    return 0;
}
