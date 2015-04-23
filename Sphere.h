#ifndef SPHERE_H
#define SPHERE_H

#define GLM_SWIZZLE

#include "SceneObject.h"
#include "glm/glm.hpp"

#include <math.h>
#include <iostream>
using namespace std;

class Sphere : public SceneObject{
private:
    glm::vec4 centerPosition;
    double radius;
    long redC;
    long greenC;
    long blueC;
public:
    Sphere(glm::vec4, double, long, long, long);
    bool isIntersected(Environment*, glm::vec3);
    void getIntersectionPoint(Environment*, double tInt, glm::vec3);
    void getColour(float &, float &, float &);
};

#endif // SPHERE_H
