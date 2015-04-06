#include "Sphere.h"

Sphere::Sphere(glm::vec4 cPos, double rad){
    centerPosition = cPos;
    radius = rad;
}

bool Sphere::isIntersected(glm::vec4 camPos, glm::vec4 camDir, double &t, glm::vec4 &intersectionPoint){
    return true;
}

void Sphere::getIntersectionPoint(glm::vec4 camP, glm::vec4 camD, double tInters, glm::vec4 &intersPoint){

}
