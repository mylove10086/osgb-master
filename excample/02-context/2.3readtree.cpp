#include <iostream>
#include <fstream>
#include <vector>
#include <Geometry.h>
#include <Osgb.h>
#include "Drawable.h"

using namespace osg;


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string base = "../data/osgb/Tile_+002_+002/";
    std::string fileurl = "../data/osgb/Tile_+002_+002/Tile_+002_+002.osgb";

    Osgb *osgb = new Osgb();
    osgb->read(fileurl);
    std::vector<Osgb *> tile;
    tile.push_back(osgb);
    int ol = tile.size();
    int index = 0;
    while (ol > index) {
        Osgb *otile = tile[index];
        index++;
        int length = otile->pagedLod.size();
        for (int i = 0; i < length; i++) {
            PagedLOD *pagedLod = otile->pagedLod[i];
            int filesize = pagedLod->filePath.size();
            if (filesize > 0) {
                for (int j = 0; j < filesize; j++) {
                    std::string path = pagedLod->filePath[j];
                    if (path.size() > 0) {
                        std::cout << base + path << std::endl;
                        Osgb *os = new Osgb();
                        os->read(base + path);
                        tile.push_back(os);
                    }
                }
            }
        }

        int glength=otile->group.size();
        for (int i = 0; i < glength; i++) {
            Group *group = otile->group[i];
            int gplength=group->pagedLod.size();
            for (int i = 0; i < gplength; i++) {
                PagedLOD *pagedLod = group->pagedLod[i];
                int filesize = pagedLod->filePath.size();
                if (filesize > 0) {
                    for (int j = 0; j < filesize; j++) {
                        std::string path = pagedLod->filePath[j];
                        if (path.size() > 0) {
                            std::cout << base + path << std::endl;
                            Osgb *os = new Osgb();
                            os->read(base + path);
                            tile.push_back(os);
                        }
                    }
                }
            }
        }
        ol = tile.size();
    }


    return 0;
}
