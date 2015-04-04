#include "Plane.h"

Plane::Plane(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::vec4 v4){
    planeMatrix = new glm::mat4(v1, v2, v3, v4);
}

bool Plane::isIntersected(){
    if(1 < 2)
        return true;
    else
        return false;
}
