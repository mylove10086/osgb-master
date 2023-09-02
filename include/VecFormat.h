/**
 *  Created by mylove on 2023/8/14. 
 */

#ifndef OSGB_MASTER_VECFORMAT_H
#define OSGB_MASTER_VECFORMAT_H
#include <iostream>
#include <vector>

namespace osg {
    class VecFormat {
    public:
        static const int ByteArray = 0x00000000;
        static const int UByteArray = 0x00000001;
        static const int ShortArray = 0x00000002;
        static const int UShortArray = 0x00000003;
        static const int IntArray = 0x00000004;
        static const int UintArray = 0x00000005;
        static const int FloatArray = 0x00000006;
        static const int DoubleArray = 0x00000007;
        static const int Vec2bArray = 0x00000008;
        static const int Vec3bArray = 0x00000009;
        static const int Vec4bArray = 0x0000000a;
        static const int Vec4ubArray = 0x0000000b;
        static const int Vec2sArray = 0x0000000c;
        static const int Vec3sArray = 0x0000000d;
        static const int Vec4sArray = 0x0000000e;
        static const int Vec2Array = 0x0000000f;
        static const int Vec3Array = 0x00000010;
        static const int Vec4Array = 0x00000011;
        static const int Vec2dArray = 0x00000012;
        static const int Vec3dArray = 0x00000013;
        static const int Vec4dArray = 0x00000014;
        static const int Vec2ubArray = 0x00000015;
        static const int Vec3ubArray = 0x00000016;
        static const int Vec2usArray = 0x00000017;
        static const int Vec3usArray = 0x00000018;
        static const int Vec4usArray = 0x00000019;
        static const int Vec2iArray = 0x0000001a;
        static const int Vec3iArray = 0x0000001b;
        static const int Vec4iArray = 0x0000001c;
        static const int Vec2uiArray = 0x0000001d;
        static const int Vec3uiArray = 0x0000001e;
        static const int Vec4uiArray = 0x0000001f;


        static unsigned int createTypedArray(std::vector<unsigned char> &, int type,int num);
    };
}


#endif //OSGB_MASTER_VECFORMAT_H
