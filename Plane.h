#ifndef PLANE_H
#define PLANE_H

#include "SceneObject.h"
#include "glm/glm.hpp"

class Plane : public SceneObject{
private:
    glm::mat4* planeMatrix;
public:
    Plane(glm::vec4, glm::vec4, glm::vec4, glm::vec4);
    bool isIntersected(glm::vec4, glm::vec4, double &);
};

#endif // PLANE_H
