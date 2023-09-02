/**
 *  Created by mylove on 2023/8/13. 
 */

#ifndef OSGB_MASTER_TEXTURE_H
#define OSGB_MASTER_TEXTURE_H

#include <iostream>

namespace osg {
    class Texture {
    public:
        int _version;
        // 用户是否自定义了纹理坐标的 x 轴方向上的扩展模式（WRAP_S）
        int8_t WRAP_S = 1;
        int xModel = 0x00002900;
        //用户是否自定义了纹理坐标的 y 轴方向上的扩展模式（WRAP_T）
        int8_t WRAP_T = 1;
        int tModel = 0x00002900;
        // 用户是否自定义了纹理坐标的 z 轴方向上的扩展模式（WRAP_R）
        int8_t WRAP_R = 1;
        int rModel = 0x00002900;
        // 用户是否自定义了缩小纹理的过滤方法（MIN_FILTER）
        int8_t min_filter = 1;
        int mlinear = 0x00002601;
        // 用户是否自定义了放大纹理的过滤方法（MAG_FILTER）
        int8_t mag_filter = 1;
        int alinear = 0x00002601;
        // 设置最大各向异性的值（MaxAnisotropy）
        float maxAnisotropy = 1.0;
        // 是否设置硬件 mipmap 生成提示（UseHardwareMipMapGeneration）
        int8_t mipmap;
        // 设置是否取消对图像数据的引用（UnRefImageDataAfterApply）
        int8_t unRefImageDataAfterApply;
        //如果图形系统支持，设置是否为纹理使用客户端存储（ClientStorageHint）
        int8_t clientStorageHint;
        // 设置是否强制纹理调整尺寸不是二次方的图像的大小（ResizeNonPowerOfTwoHint）
        int8_t resizeNonPowerOfTwoHint;
        // 设置纹理边框颜色（BorderColor），仅在纹理包装模式为“CLAMP_TO_BORDER”时使用
        double borderColor[4];
        // 设置纹理边框宽度（BorderWidth）
        float borderWidth;
        // 设置内部纹理格式模式（InternalFormatMode）
        int internalFormatMode = 0x00000000;
        // 是否将内部纹理格式模式设置为 USE_USER_DEFINED_FORMAT（使用用户自定义的纹理格式）
        int8_t USE_USER_DEFINED_FORMAT = 0x00000000;
        // 用户是否设置外部源图像格式（SourceFormat），在没有附加 osg::image 以提供源图像格式时用作备用
        int8_t sourceFormat = 0x00000000;
        // 用户是否设置外部源数据类型（SourceType），在没有附加 osg::Image 以提供源图 像格式时用作回退
        int8_t sourceType;
        // 是否将 GL_TEXTURE_COMPARE_MODE_ARB 设置为GL_COMPARE_R_TO_TEXTURE_ARB
        int8_t GL_TEXTURE_COMPARE_MODE_ARB;
        // 设置物体阴影深度缓冲比较方式（ShadowCompareFunc）
        int shadowCompareFunc;

        // 设置比较后的阴影纹理模式（ShadowTextureMode）
        int shadowTextureMode;
        // 设置环境光的阴影的值（ShadowAmbient）
        float shadowAmbient;
        // 用户是否自定义了图像附件（ImageAttachment），当前 osgb 协议是最新版本，版
        //本号在封面是 161（对应 osg 的版本是 3.6.5），而这个字段在 osgb 文件版本为 95 的时候
        //（对应的 osg 正式版本为 3.1.4）发生过一次变化，在 98 之后，添加了这个字段。之后在
        //osgb 文件版本为 154 的时候（对应最接近的的 osg 正式版本为 3.5.10）发生过一次变化，
        //在 154 之后，删除了这个字段。 osg 中的特有字段，其它引擎不用关注。
        int8_t imageAttachment;
        // 用户是否指定颜色通道（Swizzle）， 当前 osgb 协议是最新版本，版本号在封面是
        //161（对应 osg 的版本是 3.6.5），而这个字段在 osgb 文件版本为 98 的时候（对应的 osg 正
        //式版本为 3.1.8）发生过一次变化，在 98 之后，添加了这个字段。 osg 中的特有字段，其它
        //引擎不用关注。
        int8_t swizzle;
        // 设置最小细节级别值（MinLOD），当前 osgb 协议是最新版本，版本号在封面是
        //161（对应 osg 的版本是 3.6.5），而这个字段在 osgb 文件版本为 155 的时候（对应 osg 版本
        //为 3.5.10）发生过一次变化，在 155 之后，添加了这个字段。 osg 中的特有字段，其它引擎
        //不用关注。
        float minLOD = 0.0f;
        // 设置最大细节级别值（MaxLOD）， 当前 osgb 协议是最新版本，版本号在封面是
        //161（对应 osg 的版本是 3.6.5），而这个字段在 osgb 文件版本为 155 的时候（对应 osg 版本
        //为 3.5.10）发生过一次变化，在 155 之后，添加了这个字段。 osg 中的特有字段，其它引擎
        //不用关注。
        float maxLOD = -1.0f;
        // LOD 精度的偏移数值（LODBias），类似于缓冲。数值越大，缓冲越大。当前
        //osgb 协议是最新版本，版本号在封面是 161（对应 osg 的版本是 3.6.5），而这个字段在
        //osgb 文件版本为 155 的时候（对应 osg 版本为 3.5.10）发生过一次变化，在 155 之后，添
        //加了这个字段。 osg 中的特有字段，其它引擎不用关注。
        float LODBias = 0.0f;

        Texture(int );
        int regular(std::string &data, int index);

        int baseCon(std::string &data, int index);

        int contain(std::string &data, int index);

    };
}


#endif //OSGB_MASTER_TEXTURE_H
