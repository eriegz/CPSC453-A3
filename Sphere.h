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
public:
    Sphere(glm::vec4, double);
    bool isIntersected(glm::vec4, glm::vec3, double &, glm::vec3 &);
    void getIntersectionPoint(glm::vec4, glm::vec3, double, glm::vec3 &);
    unsigned char getColour();
};

#endif // SPHERE_H
