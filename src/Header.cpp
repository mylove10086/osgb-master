/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Header.h"

using namespace osg;

int Header::read(std::string &data) {
    int index = 0;
    memmove(&high, &data[0], 4);
    index += 4;
    memmove(&low, &data[4], 4);
    index += 4;
    memmove(&type, &data[8], 4);
    index += 4;
    memmove(&version, &data[12], 4);
    index += 4;
    memmove(&attribute, &data[16], 4);
    index += 4;
    memmove(&zlibl, &data[20], 4);
    index += 4;
    memmove(&zlib, &data[24], 1);
    index += 1;
    return index;
}

