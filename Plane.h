#ifndef PLANE_H
#define PLANE_H

#define GLM_SWIZZLE

#include <iostream>
using namespace std;

#include "SceneObject.h"
#include "glm/glm.hpp"

class Plane : public SceneObject{
private:
    //glm::mat4* planeMatrix;
    glm::vec4 normal, point, min, max;
    long redC;
    long greenC;
    long blueC;
public:
    Plane(glm::vec4, glm::vec4, glm::vec4, glm::vec4, long, long, long);
    bool isIntersected(glm::vec4, glm::vec3, double, glm::vec3 &);
    void getIntersectionPoint(glm::vec4, glm::vec3, double, glm::vec3 &);
    void getColour(float &, float &, float &);
};

#endif // PLANE_H
