#include "Plane.h"

Plane::Plane(glm::vec4 norm, glm::vec4 pt, glm::vec4 mi, glm::vec4 ma){
    normal = norm;
    point = pt;
    min = mi;
    max = ma;
    // ================================
    // ALL OF THE FOLLOWING CODE WORKS:
    // ================================
    /*
    cout << "point.x = " << point.x << endl;
    cout << "glm::dot(glm::vec3(norm), glm::vec3(point)) = "
         << glm::dot(glm::vec3(norm), glm::vec3(point))
         << endl;
    completelyUselessFunction(point);
    cout << "this->getPointOnPlane().x inside Plane::Plane = " << this->getPointOnPlane().x << endl;
    */
}

bool Plane::isIntersected(glm::vec4 camPos, glm::vec4 camDir, double &t, glm::vec4 &intersectionPoint){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(camPos - point)
    //           -------------------
    //              normal camDir
    //
    // If normal and camDir are perpendicular to each other, then their
    // dot product will be 0 and t will be undefined.

    /*
    cout << "camPos: " << "[" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]" << endl;
    cout << "point: " << "[" << point.x << ", " << point.y << ", " << point.z << "]" << endl;
    cout << "normal: " << "[" << normal.x << ", " << normal.y << ", " << normal.z << "]" << endl;
    cout << "camDir: " << "[" << camDir.x << ", " << camDir.y << ", " << camDir.z << "]" << endl;
    //*/

    double numerator = -1 * glm::dot(glm::vec3(normal), (glm::vec3(camPos) - glm::vec3(point)));
    double denominator = glm::dot(glm::vec3(normal), glm::vec3(camDir));
    if(denominator != 0){
        double tIntersection = numerator / denominator;
        if(tIntersection > t){
            return false;
        } else {
            /*
            cout << "camPos.x = " << camPos.x << endl;
            cout << "camPos.y = " << camPos.y << endl;
            cout << "camPos.z = " << camPos.z << endl;
            cout << "\ncamDir.x = " << camDir.x << endl;
            cout << "camDir.y = " << camDir.y << endl;
            cout << "camDir.z = " << camDir.z << endl;
            */
            getIntersectionPoint(camPos, camDir, tIntersection, intersectionPoint);
            /*
            cout << "\nintersectionPoint.x = " << intersectionPoint.x << endl;
            cout << "intersectionPoint.y = " << intersectionPoint.y << endl;
            cout << "intersectionPoint.z = " << intersectionPoint.z << endl;
            //*/
            if(intersectionPoint.x > max.x || intersectionPoint.x < min.x ||
               intersectionPoint.y > max.y || intersectionPoint.y < min.y ||
               intersectionPoint.z > max.z || intersectionPoint.z < min.z){ //If it misses the plane
                return false;
            } else { //Here, the ray is a clean hit
                return true;
            }
        }
    } else { //Divide by zero; t d.n.e.; No intersection
        return false;
    }
    return false;
}

void Plane::getIntersectionPoint(glm::vec4 camP, glm::vec4 camD, double tInters, glm::vec4 &intersPoint){
    camD *= tInters;
    /*
    cout << "\ncamP.x = " << camP.x << endl;
    cout << "camP.y = " << camP.y << endl;
    cout << "camP.z = " << camP.z << endl;
    cout << "\ncamD.x = " << camD.x << endl;
    cout << "camD.y = " << camD.y << endl;
    cout << "camD.z = " << camD.z << endl;
    */
    intersPoint = camP + camD;
}

glm::vec4 Plane::getNormalVec(){ return normal;}
glm::vec4 Plane::getPointOnPlane(){ return point;}
glm::vec4 Plane::getMinValues(){ return min;}
glm::vec4 Plane::getMaxValues(){ return max;}

void Plane::completelyUselessFunction(glm::vec4 p){
    cout << "p.x inside useless = " << p.x << endl;
}
