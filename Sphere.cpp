#include "Sphere.h"

Sphere::Sphere(glm::vec4 cPos, double rad){
    centerPosition = cPos;
    radius = rad;
}

bool Sphere::isIntersected(glm::vec4 camPos, glm::vec4 camDir, double &t, glm::vec4 &intersectionPoint){
    // d = camDir
    // D = Q - C = camPos - centerPosition
    // ||D|| = magnitude of D = glm::length(D);
    glm::vec3 D = glm::vec3(camPos) - glm::vec3(centerPosition);
    double d_D_2 = pow(glm::dot(glm::vec3(camDir), D), 2);
    double magD = glm::length(D);
    double r_2 = pow(radius, 2);
    double discriminant = d_D_2 - (magD - r_2);
    if(discriminant > 0){
        double d_D = glm::dot(glm::vec3(camDir), D);
        double temp_t_1 = (-1 * (d_D)) + sqrt(discriminant);
        double temp_t_2 = (-1 * (d_D)) - sqrt(discriminant);
        if(temp_t_1 < temp_t_2){ //Only want the intersection on the side facing the camera
            t = temp_t_1;
        } else {
            t = temp_t_2;
        }
        getIntersectionPoint(camPos, camDir, t, intersectionPoint);
    } else {
        if(discriminant == 0){ //Only one intersection on the sphere
            double d_D = glm::dot(glm::vec3(camDir), D);
            t = (-1 * (d_D));
            getIntersectionPoint(camPos, camDir, t, intersectionPoint);
        } else { //discriminant < 0; no intersections
            return false;
        }
    }
    return true;
}

void Sphere::getIntersectionPoint(glm::vec4 camP, glm::vec4 camD, double tInters, glm::vec4 &intersPoint){
    camD *= tInters;
    intersPoint = camP + camD;
}
