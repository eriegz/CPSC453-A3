#include "Plane.h"

Plane::Plane(glm::vec4 normal, glm::vec4 point, glm::vec4 min, glm::vec4 max){
    planeMatrix = new glm::mat4(normal, point, min, max);
}

bool Plane::isIntersected(glm::vec4 cam, glm::vec4 camDir, double &t){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //      t = -n(O - A)
    //           --------
    //              n d
    return true;
}
