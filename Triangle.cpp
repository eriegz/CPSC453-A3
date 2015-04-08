#include "Triangle.h"

Triangle::Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3){
    vertex1 = v1;
    vertex2 = v2;
    vertex3 = v3;
}

bool Triangle::isIntersected(glm::vec4 camPos, glm::vec3 camDir, double &t, glm::vec3 &intersectionPoint){
    return true;
}

void Triangle::getIntersectionPoint(glm::vec4 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint){

}

unsigned char Triangle::getColour(){ return (char)210; }
