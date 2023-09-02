#include <iostream>
#include <fstream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string fileurl = "../data/1536.terrain";
    fileurl = "../data/Tile_11_L24_00100000.osgb";
    fileurl = "../data/Tile_+008_+013_L21_0003300.osgb";
    //fileurl = "../data/800.terrain";
    std::ifstream ifstream;
    std::string json = "";
    ifstream.open(fileurl, std::ios::in);

    if (ifstream.is_open()) {
        json.append((std::istreambuf_iterator<char>(ifstream)), std::istreambuf_iterator<char>());
        ifstream.close();
    }
    unsigned long pos = 0;

    int header;
    int header1;
    memmove(&header, &json[0], 4);
    memmove(&header1, &json[4], 4);

    int type;//四字节整型，该位置可能为 4 个取值，分别为： 0 代表未知（UNKNOW），
    // 1 代表场景（SCENE）， 2 代表图像（IMAGE）， 3 代表对象（OBJECT），在倾斜摄影数据中，常为 1（SCENE）。
    memmove(&type, &json[8], 4);
    int version;//倾斜摄影数据所用 osgb 都为 91 版本
    memmove(&version, &json[12], 4);
    int attr;//属性位
    memmove(&attr, &json[16], 4);
    int zlibl;//位
    memmove(&zlibl, &json[20], 4);
    int8_t zlib;//
    memmove(&zlib, &json[24], 1);

    return 0;
}
