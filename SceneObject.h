#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "glm/glm.hpp"

#include <string>
using namespace std;

class SceneObject{
public:
    virtual bool isIntersected(glm::vec4, glm::vec3, double &, glm::vec3 &) = 0;
    virtual void getColour(float &, float &, float &) = 0;
};

#endif // SCENEOBJECT_H
