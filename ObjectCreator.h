#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

class ObjectCreator{
public:
    void static createScene(Plane *&, Plane *&, Plane *&, Plane *&);
    void static createSpheres(Sphere *&, Sphere *&, Sphere *&, Sphere *&);
    void static createTriangles(Triangle *&, Triangle *&, Triangle *&);
};

#endif // OBJECTCREATOR_H
