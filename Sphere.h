#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"

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

    bool isIntersected();

    double getRadius();
    double getX();
    double getY();
    double getZ();
};

#endif // SPHERE_H
