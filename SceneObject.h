#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "glm/glm.hpp"
#include "Environment.h"

#include <string>
using namespace std;

class SceneObject{
public:
    virtual bool isIntersected(Environment*, glm::vec3) = 0;
    virtual void getColour(float &, float &, float &) = 0;
    virtual void getSpecular(double &) = 0;
};

#endif // SCENEOBJECT_H
