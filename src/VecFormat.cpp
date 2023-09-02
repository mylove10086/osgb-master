/**
 *  Created by mylove on 2023/8/14. 
 */

#include "VecFormat.h"

using namespace osg;

unsigned int VecFormat::createTypedArray(std::vector<unsigned char> &typeArray, int type, int num) {
    unsigned int size = 0;
    switch (type) {
        case VecFormat::Vec3Array:
            size = 3 * num * 4;
            typeArray.resize(size);
            break;
        case VecFormat::Vec2Array:
            size = 2 * num * 4;
            typeArray.resize(size);
            break;
        default:
            int *i = NULL;
            *i = 0;
            break;
    }
    return size;
}
