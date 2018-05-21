#ifndef HANGAR_CONTROLLER_H
#define HANGAR_CONTROLLER_H

#include "hangar.h"
#include "box.h"
#include "vertex.h"
#include <QVector3D>

namespace controller {
using namespace model;

class HangarController{

public:
    ~HangarController();
    void addBox(int x, int y, int z);
    void removeBox(int x, int y, int z);


    void generateVertexes();

public:
    Vertex* sg_vertexes = nullptr;

private:
    Hangar hangar;
};

}

#endif // HANGAR_CONTROLLER_H
