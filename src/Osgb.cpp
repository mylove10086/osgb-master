/**
 *  Created by mylove on 2023/8/12. 
 */

#include "Osgb.h"
#include <fstream>

using namespace osg;

bool Osgb::read(std::string filePath) {
    std::ifstream ifstream;
    std::string json = "";
    _path = filePath;
    ifstream.open(filePath, std::ios::in);
    if (ifstream.is_open()) {
        json.append((std::istreambuf_iterator<char>(ifstream)), std::istreambuf_iterator<char>());
        ifstream.close();
    }
    header = new Header;
    if (json.size() == 0) {
        return false;
    }
    int index = header->read(json);
    Osgb::readBody(json, index);
    return true;
}

int Osgb::readBody(std::string &data, int index) {
    std::cout << "开始读取 " << _path << std::endl;

    size_t length = data.size();
    while (true) {
        int cl;
        memmove(&cl, &data[index], 4);
        index += 4;
        std::string cname;
        cname.resize(cl);
        memmove(&cname[0], &data[index], cl);
        index = index + cl;
        if (cname == "osg::PagedLOD") {
            PagedLOD *lod = new PagedLOD(this->header->version);
            lod->classname = "osg::PagedLOD";
            index = lod->regular(data, index);
            index = lod->inheritance(data, index);
            index = lod->contain(data, index);
            pagedLod.push_back(lod);
        } else if (cname == "osg::Geode") {
            Geode *g = new Geode(this->header->version);
            g->classname = "osg::Geode";
            index = g->regular(data, index);
            index = g->inheritance(data, index);
            index = g->contain(data, index);
            geode.push_back(g);
        } else if (cname == "osg::Group") {
            Group *g = new Group(this->header->version);
            g->classname = "osg::Group";
            index = g->regular(data, index);
            index = g->inheritance(data, index);
            index = g->contain(data, index);
            group.push_back(g);
        } else {
            Node* _node = new Node(this->header->version);
            _node->classname = "osg::Node";
            index = _node->regular(data, index);
            index = _node->inheritance(data, index);
            index = _node->contain(data, index);
            //std::string *sst = NULL;
            //*sst = "";
        }
        if (length <= index) {
            std::cout << _path << " 读取完成" << std::endl;
            if (length != index) {
                std::cout << _path << " 读取出错了 请查查代码吧" << std::endl;
                std::string *str = NULL;
                *str = "";
            }
            break;
        }
    }
    return index;
}




