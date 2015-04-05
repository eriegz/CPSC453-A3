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

bool Plane::isIntersected(glm::vec4 cam, glm::vec4 camDir, double &t){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(cam - point)
    //           -------------------
    //              normal camDir
    //

    cout << "cam: " << "[" << cam.x << ", " << cam.y << ", " << cam.z << "]" << endl;
    cout << "point: " << "[" << point.x << ", " << point.y << ", " << point.z << "]" << endl;
    cout << "normal: " << "[" << normal.x << ", " << normal.y << ", " << normal.z << "]" << endl;
    cout << "camDir: " << "[" << camDir.x << ", " << camDir.y << ", " << camDir.z << "]" << endl;

    double numerator = -1 * glm::dot(glm::vec3(getNormalVec()), (glm::vec3(cam) - glm::vec3(point)));
    double denominator = glm::dot(glm::vec3(getNormalVec()), glm::vec3(camDir));
    cout << "\nnumerator / denominator = " << numerator / denominator << endl;
    return true;
}

glm::vec4 Plane::getNormalVec(){ return normal;}
glm::vec4 Plane::getPointOnPlane(){ return point;}
glm::vec4 Plane::getMinValues(){ return min;}
glm::vec4 Plane::getMaxValues(){ return max;}

void Plane::completelyUselessFunction(glm::vec4 p){
    cout << "p.x inside useless = " << p.x << endl;
}

bool Plane::isIntersected2(glm::vec4 cam, glm::vec4 camDir, double &t){
    // If the viewing ray intersects the plane defined in this class's
    // private variables, there should exist some t for which:
    //
    //      t = -normal(cam - point)
    //           -------------------
    //              normal camDir
    //
    //double denominator = ;

    glm::vec4 myTestVec4(1, 1, 1, 1);
    myTestVec4;
    cout << "point.x = " << point.x << endl;
    /*
    cout << "glm::dot(glm::vec3(cam), glm::vec3(myTestVec4)) = "
         << glm::dot(glm::vec3(cam), glm::vec3(myTestVec4))
         << endl;
    */

    /*
    cout << "cam - getPointOnPlane() = "
         << glm::dot(glm::vec3(getNormalVec()), (glm::vec3(cam) - glm::vec3(getPointOnPlane())))
         << endl;
    */
    return true;
}
