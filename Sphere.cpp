#include "Sphere.h"

Sphere::Sphere(glm::vec4 cPos, double rad, long red, long green, long blue, double kS){
    centerPosition = cPos;
    radius = rad;
    redC = red;
    greenC = green;
    blueC = blue;
    kSpecular = kS;
}

bool Sphere::isIntersected(Environment *myEnv, glm::vec3 rayDir){
    // d = camDir
    // D = Q - C = camPos - centerPosition
    // ||D||^2 = (magnitude of D)^2 = (glm::length(D))^2;
    //
    glm::vec3 D = glm::vec3(myEnv->camPosition) - glm::vec3(centerPosition);
    double d_D_2 = pow(glm::dot(glm::vec3(rayDir), D), 2);
    double magD_2 = pow(glm::length(D), 2);
    double r_2 = pow(radius, 2);
    double discriminant = d_D_2 - (magD_2 - r_2);
    if(discriminant > 0){
        double d_D = glm::dot(glm::vec3(rayDir), D);
        double tIntersection_1 = (-1 * (d_D)) + sqrt(discriminant);
        double tIntersection_2 = (-1 * (d_D)) - sqrt(discriminant);

        if((fabs(tIntersection_1) < 0.01 && fabs(tIntersection_2) < 0.01) ||        //Both zero
                (fabs(tIntersection_1) < 0.01 && tIntersection_2 < -0.01) ||        //1st is 0, 2nd is neg
                (tIntersection_1 < -0.01 && fabs(tIntersection_2) < 0.01) ||        //1st is neg, 2nd is 0
                (tIntersection_1 < -0.01 && tIntersection_2 < -0.01)){              //Both negative
            return false;              //Both negative
        }

        // Because intersPoint gets set with every new intersection calculation, we want to be able
        // to restore the previous intersection point if the new one is without the limits of the plane.
        glm::vec3 intersPoint_backup = myEnv->intersPoint;
        double tValueBackup = myEnv->tValue;

        // Next, if both numbers are positive, use the smaller one
        if(tIntersection_1 > 0.01 && tIntersection_2 > 0.01){
            if(tIntersection_1 < tIntersection_2){
                getIntersectionPoint(myEnv, tIntersection_1, rayDir);
                myEnv->tValue = tIntersection_1;
            } else {
                getIntersectionPoint(myEnv, tIntersection_2, rayDir);
                myEnv->tValue = tIntersection_2;
            }
        } else
        // Next, if either of the numbers is positive use it
        if(tIntersection_1 > 0.01){
            getIntersectionPoint(myEnv, tIntersection_1, rayDir);
            myEnv->tValue = tIntersection_1;
        } else {
            if(tIntersection_2 > 0.01){
                getIntersectionPoint(myEnv, tIntersection_2, rayDir);
                myEnv->tValue = tIntersection_2;
            }
        }
    } else return false;
//    glm::vec3 tempNorm = myEnv->intersPoint - glm::vec3(centerPosition);
//    myEnv->intersNorm.x = tempNorm.x;
//    myEnv->intersNorm.y = tempNorm.y;
//    myEnv->intersNorm.z = tempNorm.z;
    return true; //Putting this here b/c there are many ways in which we can return true
}

void Sphere::getIntersectionPoint(Environment *myEnv, double tInt, glm::vec3 rayDir){
    rayDir *= tInt;
    myEnv->intersPoint = myEnv->camPosition + rayDir;
//    cout << "myEnv->intersPoint = [" << myEnv->intersPoint.x << ", " << myEnv->intersPoint.y << ", " << myEnv->intersPoint.z << "]" << endl;
}

void Sphere::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}

void Sphere::getSpecular(double &kS){
    kS = kSpecular;
}
