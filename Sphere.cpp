#include "Sphere.h"

Sphere::Sphere(glm::vec4 cPos, double rad, long red, long green, long blue){
    centerPosition = cPos;
    radius = rad;
    redC = red;
    greenC = green;
    blueC = blue;
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

//        cout << "\nInside Sphere::isIntersected..." << endl;
//        cout << "myEnv->camPosition = ["
//             << myEnv->camPosition.x << ", "
//             << myEnv->camPosition.y << ", "
//             << myEnv->camPosition.z << "]" << endl;
//            cout << "rayDir = "
//                 << rayDir.x << ", "
//                 << rayDir.y << ", "
//                 << rayDir.z << "]" << endl;
//        cout << "tIntersection_1 = " << tIntersection_1 << ", tIntersection_2 = " << tIntersection_2 << endl;// If both numbers are zero, or negative, return false

        if(fabs(tIntersection_1) < 0.01 && fabs(tIntersection_2) < 0.01) return false;    //Both zero
        if(fabs(tIntersection_1) < 0.01 && tIntersection_2 < -0.01) return false;         //1st is 0, 2nd is neg
        if(tIntersection_1 < -0.01 && fabs(tIntersection_2) < 0.01) return false;         //1st is neg, 2nd is 0
        if(tIntersection_1 < -0.01 && tIntersection_2 < -0.01) return false;              //Both negative

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
    return true;
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
