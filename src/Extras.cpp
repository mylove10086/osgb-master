/**
 * Created by IBM on 2022/5/13.
 */

#include "Extras.h"

using namespace osg;

Extras::Extras() {
    _pipeline = new Pipeline();
}

Extras::~Extras() {
    delete _pipeline;
    _pipeline = NULL;
}

