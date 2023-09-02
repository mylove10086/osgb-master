/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_STATESET_H
#define OSGB_MASTER_STATESET_H

#include <iostream>
#include <vector>
#include "Object.h"
#include "Material.h"
#include "Texture2D.h"

namespace osg {
    class StateSet {
    public:
        int _version;

        //类长度
        int length;
        int identifier;
        std::string classname = "";

        // 用户是否自定义了模式列表（ModeList）， Mode 代表控制渲染时的一些状态的开关比如灯光是否定义
        int8_t modeList = 0;
        // 用户是否自定义了属性列表（AttributeList）
        int8_t attributeList = 0;
        int attributeNum = 0;
        std::vector<Material *> _material;
        int materialState = 0x00000000;


        //用户是否自定义了纹理模式列表（TextureModeList）
        int8_t textureModeList = 0;
        int textureModeNum = 0;
        //std::vector<int[3]> textureMode;


        // 用户是否自定义了纹理属性列表TextureAttributeList
        int8_t textureAttributeList = 0;
        int textureAttributeNum = 0;
        int textureNum = 0;
        std::vector<Texture2D *> _texture;
        int textureState = 0x00000000;


        //用户是否自定义了一致变量列表
        int8_t uniformList = 0;

        //设置渲染提示（RenderingHint）
        int renderingHint = 0;
        //设置渲染属性模式 （RenderBinmode）
        int renderBinmode = 0;
        //设置渲染编号 （BinNumber）
        int binNumber = 0;
        //设置渲染名称（BinName） ，不同名称对应不同排序方式
        std::string binName = "";
        // 是否允许渲染嵌套（NestRenderBins）
        int8_t nestRenderBins = 1;
        // 更新阶段的回调（UpdateCallback）是否加入到 osgb 的序列化中， osg 中的特有
        //字段，其它引擎不用关注。
        int8_t updateCallback = 0;
        // 事件阶段的回调（EventCallback）是否加入到 osgb 的序列化中， osg 中的特有字
        //段，其它引擎不用关注
        int8_t eventCallback = 0;
        // 用户是否设置要传递给着色器的定义列表（DefineList） ,当前 osgb 协议是最新版
        //本，版本号在封面是 161（对应 osg 的版本是 3.6.5），而这个字段在 osgb 文件版本为 151
        //的时候（对应最接近的 osg 正式版本为 3.5.8）发生过一次变化，在 151 之后，添加了这个
        //字段。 osg 中的特有字段，其它引擎不用关注。
        int8_t defineList = 0;


        Object *_object = NULL;

        StateSet(int version);

        int regular(std::string &data, int index);

        int inheritance(std::string &data, int index);

        int contain(std::string &data, int index);

    };
}


#endif //OSGB_MASTER_STATESET_H
