#include "Plane.h"

Plane::Plane(glm::vec3 norm, glm::vec3 pt, glm::vec3 mi, glm::vec3 ma, long red, long green, long blue){
    normal = norm;
    point = pt;
    min = mi;
    max = ma;
    redC = red;
    greenC = green;
    blueC = blue;
}

bool Plane::isIntersected(Environment *myEnv, glm::vec3 rayDir){
    // Make local copies of everything first for simplicity.
    // Store any values to be saved inside myEnv later.
    glm::vec3 camPos = myEnv->camPosition;
    double t = myEnv->tValue;
    glm::vec3 intPt = myEnv->intersPoint;
    glm::vec3 intNrm = myEnv->intersNorm;

    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(camPos - point)
    //           -------------------
    //              normal camDir
    //
    // If normal and camDir are perpendicular to each other, then their
    // dot product will be 0 and t will be undefined.

//    cout << "=======INSIDE PLANE========" << endl;
//    cout << "\ncamPos: " << "[" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]" << endl;
//    cout << "point: " << "[" << point.x << ", " << point.y << ", " << point.z << "]" << endl;
//    cout << "normal: " << "[" << normal.x << ", " << normal.y << ", " << normal.z << "]" << endl;
//    cout << "camDir: " << "[" << camDir.x << ", " << camDir.y << ", " << camDir.z << "]" << endl;
//    cout << "camPos - point = [" << camPMinusPt.x << ", " << camPMinusPt.y << ", " << camPMinusPt.z << "]" << endl;
//    cout << "glm::dot(glm::vec3(normal), camPMinusPt) = " << test2 << endl;

    double numerator = (-1) * glm::dot(glm::vec3(normal), (glm::vec3(camPos) - glm::vec3(point)));
    double denominator = glm::dot(glm::vec3(normal), glm::vec3(rayDir));
    if(denominator != 0){
        double tIntersection = numerator / denominator;
        if(tIntersection > t){
            return false;
        } else {
            getIntersectionPoint(myEnv, tIntersection, rayDir);
            if(myEnv->intersPoint.x > max.x || myEnv->intersPoint.x < min.x ||
               myEnv->intersPoint.y > max.y || myEnv->intersPoint.y < min.y ||
               myEnv->intersPoint.z > max.z || myEnv->intersPoint.z < min.z){ //If it misses the plane
                return false;
            } else { //Here, the ray is a clean hit
                myEnv->tValue = tIntersection;
//                cout << "[SUCCESSFUL PLANE HIT] myEnv->tValue = " << myEnv->tValue << endl;
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
    //glm::vec3 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint
    glm::vec3 camP = myEnv->camPosition;

//    cout << "rayDir = ["
//         << rayDir.x << ", "
//         << rayDir.y << ", "
//         << rayDir.z << "]" << endl;

    rayDir *= tInt;

    myEnv->intersPoint = camP + rayDir;

//    cout << "myEnv->camPosition = ["
//         << myEnv->camPosition.x << ", "
//         << myEnv->camPosition.y << ", "
//         << myEnv->camPosition.z << "]" << endl;
//    cout << "rayDir *= " << tInt << " = ["
//         << rayDir.x << ", "
//         << rayDir.y << ", "
//         << rayDir.z << "]" << endl;
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
