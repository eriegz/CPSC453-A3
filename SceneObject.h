#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "glm/glm.hpp"

#include <string>
using namespace std;

class SceneObject{
public:
    virtual bool isIntersected(glm::vec4, glm::vec4, double &) = 0;
    //virtual string getObjectType();
};

#endif // SCENEOBJECT_H
