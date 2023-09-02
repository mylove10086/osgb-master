#include <iostream>
#include <fstream>
#include <vector>
#include <Geometry.h>
#include <Osgb.h>
#include "Drawable.h"

using namespace osg;

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string fileurl = "../data/1536.terrain";
    fileurl = "../data/Tile_11_L24_00100000.osgb";
    fileurl = "../data/Tile_5_L21_002240t1.osgb";
    //fileurl = "../data/Tile_13_L25_000154000.osgb";
    //fileurl = "../data/Tile_+002_+002_L16_00.osgb";
    //fileurl = "../data/Tile_+008_+013_L21_0003300.osgb";
    fileurl = "../data/Tile_+003_+013.osgb";

    Osgb osgb;
    osgb.read(fileurl);

    return 0;
}
