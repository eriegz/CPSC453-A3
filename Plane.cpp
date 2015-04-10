#include "Plane.h"

Plane::Plane(glm::vec4 norm, glm::vec4 pt, glm::vec4 mi, glm::vec4 ma, long red, long green, long blue){
    normal = norm;
    point = pt;
    min = mi;
    max = ma;
    redC = red;
    greenC = green;
    blueC = blue;
}

bool Plane::isIntersected(glm::vec4 camPos, glm::vec3 camDir, double &t, glm::vec3 &intersectionPoint){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(camPos - point)
    //           -------------------
    //              normal camDir
    //
    // If normal and camDir are perpendicular to each other, then their
    // dot product will be 0 and t will be undefined.

//    cout << "\ncamPos: " << "[" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]" << endl;
//    cout << "point: " << "[" << point.x << ", " << point.y << ", " << point.z << "]" << endl;
//    cout << "normal: " << "[" << normal.x << ", " << normal.y << ", " << normal.z << "]" << endl;
//    cout << "camDir: " << "[" << camDir.x << ", " << camDir.y << ", " << camDir.z << "]" << endl;
    glm::vec3 test = glm::vec3(camPos) - glm::vec3(point);
//    cout << "camPos - point = [" << test.x << ", " << test.y << ", " << test.z << "]" << endl;
    double test2 = glm::dot(glm::vec3(normal), test);
//    cout << "glm::dot(glm::vec3(normal), test) = " << test2 << endl;

    double numerator = (-1) * glm::dot(glm::vec3(normal), (glm::vec3(camPos) - glm::vec3(point)));
    double denominator = glm::dot(glm::vec3(normal), glm::vec3(camDir));
    if(denominator != 0){
        double tIntersection = numerator / denominator;
        if(tIntersection > t){
            return false;
        } else {
            getIntersectionPoint(camPos, camDir, tIntersection, intersectionPoint);
            if(intersectionPoint.x > max.x || intersectionPoint.x < min.x ||
               intersectionPoint.y > max.y || intersectionPoint.y < min.y ||
               intersectionPoint.z > max.z || intersectionPoint.z < min.z){ //If it misses the plane
//                cout << "denominator = " << denominator << endl;
//                cout << "normal.x = " << normal.x << endl;
//                cout << "normal.y = " << normal.y << endl;
//                cout << "normal.z = " << normal.z << endl;
//                cout << "camDir.x = " << camDir.x << endl;
//                cout << "camDir.y = " << camDir.y << endl;
//                cout << "camDir.z = " << camDir.z << endl;
//                cout << "intersectionPoint.x = " << intersectionPoint.x << endl;
//                cout << "intersectionPoint.y = " << intersectionPoint.y << endl;
//                cout << "intersectionPoint.z = " << intersectionPoint.z << endl;
                return false;
            } else { //Here, the ray is a clean hit
                t = tIntersection;
//                cout << "[SUCCESSFUL HIT] t = " << t << endl;
                return true;
            }
        }
    } else { //Divide by zero; t d.n.e.; No intersection
        return false;
    }
}

void Plane::getIntersectionPoint(glm::vec4 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint){
    camD *= tInters;

    intersPoint = glm::vec3(camP) + camD;
    // C++ has trouble with floating point arithmetic, so I have to pick up the slack.
    if(fabs(intersPoint.x) < 0.00001){ intersPoint.x = 0; }
    if(fabs(intersPoint.y) < 0.00001){ intersPoint.y = 0; }
    if(fabs(intersPoint.z) < 0.00001){ intersPoint.z = 0; }
    if(fabs(intersPoint.x - max.x) < 0.00001){ intersPoint.x = max.x; }
    if(fabs(intersPoint.y - max.y) < 0.00001){ intersPoint.y = max.y; }
    if(fabs(intersPoint.z - max.z) < 0.00001){ intersPoint.z = max.z; }

//    cout << "\nInside Plane::getIntersectionPoint..." << endl;
//    cout << "tInters = " << tInters << endl;
//    cout << "intersPoint = (" << intersPoint.x << ", " << intersPoint.y << ", " << intersPoint.z << ")" << endl;
//    cout << "camD.x = " << camD.x << endl;
//    cout << "camD.y = " << camD.y << endl;
//    cout << "camD.z = " << camD.z << endl;
//    cout << "camP.x = " << camP.x << endl;
//    cout << "camP.y = " << camP.y << endl;
//    cout << "camP.z = " << camP.z << endl;
}

void Plane::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}
