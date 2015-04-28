#include "Plane.h"

Plane::Plane(glm::vec3 norm, glm::vec3 pt, glm::vec3 mi, glm::vec3 ma, long red, long green, long blue, double kS){
    normal = norm;
    point = pt;
    min = mi;
    max = ma;
    redC = red;
    greenC = green;
    blueC = blue;
    kSpecular = kS;
}

bool Plane::isIntersected(Environment *myEnv, glm::vec3 rayDir){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(camPos - point)
    //           -------------------
    //              normal camDir
    //
    // If normal and camDir are perpendicular to each other, then their
    // dot product will be 0 and t will be undefined.

    double numerator = (-1) * glm::dot(glm::vec3(normal), (glm::vec3(myEnv->camPosition) - glm::vec3(point)));
    double denominator = glm::dot(glm::vec3(normal), glm::vec3(rayDir));
    if(denominator != 0){
        double tIntersection = numerator / denominator;
//        cout << "tIntersection = " << tIntersection << endl;
//        cout << "myEnv->tValue = " << myEnv->tValue << endl;
        if(tIntersection > myEnv->tValueMax || tIntersection < 0 || fabs(tIntersection) < 0.0001){ //If it's too far, or behind the camera
            return false;
        } else {
            // Because intersPoint gets set with every new intersection calculation, we want to be able
            // to restore the previous intersection point if the new one is without the limits of the plane.
            glm::vec3 intersPoint_Backup = myEnv->intersPoint;
            glm::vec3 intersNorm_Backup = myEnv->intersNorm;
            glm::vec3 camDirection_Backup = myEnv->camDirection;
            glm::vec3 camPosition_Backup = myEnv->camPosition;
            double tValueMax_Backup = myEnv->tValueMax;

            getIntersectionPoint(myEnv, tIntersection, rayDir);
            if(myEnv->intersPoint.x > max.x || myEnv->intersPoint.x < min.x ||
               myEnv->intersPoint.y > max.y || myEnv->intersPoint.y < min.y ||
               myEnv->intersPoint.z > max.z || myEnv->intersPoint.z < min.z){ //If it misses the plane
                myEnv->intersPoint = intersPoint_Backup; //Reset values
                myEnv->intersNorm = intersNorm_Backup;
                myEnv->camDirection = camDirection_Backup;
                myEnv->camPosition = camPosition_Backup;
                myEnv->camDirection = camDirection_Backup;
                myEnv->tValueMax = tValueMax_Backup;
                return false;
            } else { //Here, the ray is a clean hit
                myEnv->tValue = tIntersection;
                //cout << "Setting plane intersection normal as [" << normal.x << ", " << normal.y << ", " << normal.z << "]" << endl;
                myEnv->intersNorm.x = normal.x;
                myEnv->intersNorm.y = normal.y;
                myEnv->intersNorm.z = normal.z;
                return true;
            }
        }
    } else { //Divide by zero; t d.n.e.; No intersection
        return false;
    }
}

void Plane::getIntersectionPoint(Environment *myEnv, double tInt, glm::vec3 rayDir){
//    cout << "tInt = " << tInt << endl;
    rayDir *= tInt;
    myEnv->intersPoint = myEnv->camPosition + rayDir;
//    cout << "myEnv->intersPoint = ["
//         << myEnv->intersPoint.x << ", "
//         << myEnv->intersPoint.y << ", "
//         << myEnv->intersPoint.z << "]" << endl;

    // C++ has trouble with floating point arithmetic, so I have to pick up the slack.
    if(fabs(myEnv->intersPoint.x) < 0.00001){ myEnv->intersPoint.x = 0; }
    if(fabs(myEnv->intersPoint.y) < 0.00001){ myEnv->intersPoint.y = 0; }
    if(fabs(myEnv->intersPoint.z) < 0.00001){ myEnv->intersPoint.z = 0; }
    if(fabs(myEnv->intersPoint.x - max.x) < 0.00001){ myEnv->intersPoint.x = max.x; }
    if(fabs(myEnv->intersPoint.y - max.y) < 0.00001){ myEnv->intersPoint.y = max.y; }
    if(fabs(myEnv->intersPoint.z - max.z) < 0.00001){ myEnv->intersPoint.z = max.z; }
}

void Plane::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}

void Plane::getSpecular(double &kS){
    kS = kSpecular;
}
