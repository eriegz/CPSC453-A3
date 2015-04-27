#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

#include <vector>

class ObjectCreator{
public:
    void static createScene(Plane *&, Plane *&, Plane *&, Plane *&);
    void static createSpheres(Sphere *&, Sphere *&, Sphere *&, Sphere *&);
    void static createTriangles(Triangle *&, Triangle *&, Triangle *&, Triangle *&);
    void static initializeMyObjects(vector<SceneObject*> &);
};

#endif // OBJECTCREATOR_H
