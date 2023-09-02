/**
 *  Created by mylove on 2023/8/12. 
 */

#ifndef OSGB_MASTER_OSGB_H
#define OSGB_MASTER_OSGB_H

#include <iostream>
#include <vector>
#include <Header.h>
#include <PagedLOD.h>
#include <Geode.h>
#include <Group.h>

namespace osg {
    class Osgb {
    public:
        std::string _path = "";
        Header *header = NULL;

        std::vector<PagedLOD *> pagedLod;
        std::vector<Geode *> geode;
        std::vector<Group *> group;


        bool read(std::string filePath);

        int readBody(std::string &data, int index);

    };
}


#endif //OSGB_MASTER_OSGB_H
