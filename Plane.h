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
    glm::vec3 normal, point, min, max;
    long redC;
    long greenC;
    long blueC;
    double kDiffuse;
    double kSpecular;
public:
    Plane(glm::vec3, glm::vec3, glm::vec3, glm::vec3, long, long, long, double, double);
    bool isIntersected(Environment*, glm::vec3);
    void getIntersectionPoint(Environment*, double tInt, glm::vec3);
    void getColour(float &, float &, float &);
    void getDiffuse(double &);
    void getSpecular(double &);
};

#endif // PLANE_H
