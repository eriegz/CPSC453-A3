#include "Sphere.h"

Sphere::Sphere(glm::vec4 cPos, double rad, long red, long green, long blue){
    centerPosition = cPos;
    radius = rad;
    redC = red;
    greenC = green;
    blueC = blue;
}

bool Sphere::isIntersected(Environment *myEnv, glm::vec3 rayDir){
    // Make local copies of everything because shut up
    glm::vec3 camPos = myEnv->camPosition;
    double t = myEnv->tValue;
    glm::vec3 intPt = myEnv->intersPoint;
    glm::vec3 intNrm = myEnv->intersNorm;

    // d = camDir
    // D = Q - C = camPos - centerPosition
    // ||D||^2 = (magnitude of D)^2 = (glm::length(D))^2;
    //
    glm::vec3 D = glm::vec3(camPos) - glm::vec3(centerPosition);
    double d_D_2 = pow(glm::dot(glm::vec3(rayDir), D), 2);
    double magD_2 = pow(glm::length(D), 2);
    double r_2 = pow(radius, 2);
    double discriminant = d_D_2 - (magD_2 - r_2);
    if(discriminant > 0){
        double d_D = glm::dot(glm::vec3(rayDir), D);
        double tIntersection_1 = (-1 * (d_D)) + sqrt(discriminant);
        double tIntersection_2 = (-1 * (d_D)) - sqrt(discriminant);
//        cout << "\nInside Sphere::isIntersected..." << endl;
//        cout << "tIntersection_1 = " << tIntersection_1 << ", tIntersection_2 = " << tIntersection_2 << endl;
        if(tIntersection_1 < tIntersection_2){ //We only want the intersection on the side facing the camera
            getIntersectionPoint(camPos, rayDir, tIntersection_1, intPt);
            myEnv->tValue = tIntersection_1;
//            cout << "getIntersectionPoint(..., tIntersection_1) is called" << endl;
//            cout << "t = " << t << endl;
        } else {
            getIntersectionPoint(camPos, rayDir, tIntersection_2, intPt);
            myEnv->tValue = tIntersection_2;
            //cout << "getIntersectionPoint(..., tIntersection_2) is called" << endl;
            //cout << "t = " << t << endl;
        }
    } else {
        if(discriminant == 0){ //Only one intersection on the sphere
            double d_D = glm::dot(glm::vec3(rayDir), D);
            double tIntersection = (-1 * (d_D));
            getIntersectionPoint(camPos, rayDir, tIntersection, intPt);
            myEnv->tValue = tIntersection;
        } else { //discriminant < 0; no intersections
            return false;
        }
    }
    glm::vec3 tempNorm = intPt - glm::vec3(centerPosition);
    myEnv->intersNorm.x = tempNorm.x;
    myEnv->intersNorm.y = tempNorm.y;
    myEnv->intersNorm.z = tempNorm.z;
    return true;
}

void Sphere::getIntersectionPoint(glm::vec3 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint){
    camD *= tInters;
    intersPoint = glm::vec3(camP) + camD;
}

void Sphere::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}
