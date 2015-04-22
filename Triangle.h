#ifndef TRIANGLE_H
#define TRIANGLE_H

#define GLM_SWIZZLE

#include "SceneObject.h"
#include "Plane.h"

#include "glm/glm.hpp"

#include <iostream>
using namespace std;

class Triangle : public SceneObject{
private:
    glm::vec3 vertex1, vertex2, vertex3;
    long redC;
    long greenC;
    long blueC;
public:
    Triangle(glm::vec3, glm::vec3, glm::vec3, long, long, long);
    bool isIntersected(Environment*, glm::vec3);
    void getIntersectionPoint(glm::vec3, glm::vec3, double, glm::vec3 &);
    void getColour(float &, float &, float &);
};

#endif // TRIANGLE_H
