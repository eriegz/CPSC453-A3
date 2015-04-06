#ifndef TRIANGLE_H
#define TRIANGLE_H

#define GLM_SWIZZLE

#include "SceneObject.h"
#include "glm/glm.hpp"

#include <iostream>
using namespace std;

class Triangle : public SceneObject{
private:
    glm::vec4 vertex1, vertex2, vertex3;
public:
    Triangle(glm::vec4, glm::vec4, glm::vec4);
    bool isIntersected(glm::vec4, glm::vec4, double &, glm::vec4 &);
    void getIntersectionPoint(glm::vec4, glm::vec4, double, glm::vec4 &);
};

#endif // TRIANGLE_H
