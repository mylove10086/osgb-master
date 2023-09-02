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
    size_t size = osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data.size();
    FILE *file = fopen("../data/test.jpeg", "wb");
    fwrite(&(osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data)[0],
           sizeof(unsigned char), size, file);
    fclose(file);

    glb->writeGlb("../data/out","Tile_+006_+006_L17_000");
    return 0;

}
