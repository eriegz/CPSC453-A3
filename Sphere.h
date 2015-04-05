#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"
#include "glm/glm.hpp"

#include <iostream>
using namespace std;

class Sphere : public SceneObject{
private:
    double radius;

    double xCoor;
    double yCoor;
    double zCoor;

public:
    Sphere(double, double, double, double);

    bool isIntersected(glm::vec4, glm::vec4, double &);

    double getRadius();
    double getX();
    double getY();
    double getZ();
};

#endif // SPHERE_H
