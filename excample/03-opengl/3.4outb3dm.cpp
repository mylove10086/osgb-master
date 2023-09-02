#include <iostream>
#include <fstream>
#include <vector>
#include <Osgb.h>
#include <Glb.h>

using namespace osg;

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string fileurl = "../data/1536.terrain";
    fileurl = "../data/Tile_11_L24_00100000.osgb";

    Osgb osgb;

    osgb.read(fileurl);

    Glb *glb=Glb::parse(&osgb);
    glb->writeB3dm("../data/out","Tile_+010_+009_L17_000");
    return 0;
}
