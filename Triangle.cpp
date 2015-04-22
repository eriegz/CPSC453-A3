#include "Triangle.h"

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, long red, long green, long blue){
    vertex1 = v1;
    vertex2 = v2;
    vertex3 = v3;
    redC = red;
    greenC = green;
    blueC = blue;
}

bool Triangle::isIntersected(Environment *myEnv, glm::vec3 rayDir){
    // For this algorithm, first we will calculate the ray's intersection with
    // the plane which the triangle sits in to get a point, P1. We can then
    // see if this point is within the triangle limits.
    //
    // Let V0 = vertex1, V1 = vertex2, and V2 = vertex3
    //      u = V1 - V0 = vertex2 - vertex1
    //      v = V2 - V0 = vertex3 - vertex1
    //      n = cross(u, v)
    //      w = P1 - V0 = intersectionPoint - vertex2
    //
    //  ...and parametric coordinates for the point of intersection are:
    //
    //      s = (u . v)(w . v) - (v . v)(w . u)
    //          -------------------------------
    //            (u . v)^2 - (u . u)(v . v)
    //
    //      t = (u . v)(w . u) - (u . u)(w . v)
    //          -------------------------------
    //                  ...same

    glm::vec3 u = vertex2 - vertex1;
    glm::vec3 v = vertex3 - vertex1;
    glm::vec3 n = glm::cross(u, v);
    if(fabs(n.x) < 0.00001){ n.x = 0; }
    if(fabs(n.y) < 0.00001){ n.y = 0; }
    if(fabs(n.z) < 0.00001){ n.z = 0; }
    glm::vec3 n_norm = glm::normalize(n);

    glm::vec3 tempMin(-999999, -999999, -999999); //Simulating an infinite plane
    glm::vec3 tempMax(999999, 999999, 999999);
    Plane::Plane tempPlane(n_norm, vertex2, tempMin, tempMax, 0, 0, 0);

    if(tempPlane.isIntersected(myEnv, rayDir) == true){
//        cout << "Ray intersects with the plane the triangle sits in." << endl;
        glm::vec3 w = myEnv->intersPoint - vertex1;
        if(fabs(w.x) < 0.00001){ w.x = 0; }
        if(fabs(w.y) < 0.00001){ w.y = 0; }
        if(fabs(w.z) < 0.00001){ w.z = 0; }

        double num1Part1 = glm::dot(u, v); double num1Part2 = glm::dot(w, v);
        double num1Part3 = glm::dot(v, v); double num1Part4 = glm::dot(w, u);
        double numerator1 = (num1Part1 * num1Part2) - (num1Part3 * num1Part4);

        double num2Part1 = num1Part1; double num2Part2 = glm::dot(w, u);
        double num2Part3 = glm::dot(u, u); double num2Part4 = glm::dot(w, v);
        double numerator2 = (num2Part1 * num2Part2) - (num2Part3 * num2Part4);

        double denomPart1 = pow(num1Part1, 2);
        double denomPart2 = num2Part3; double denomPart3 = num1Part3;
        double denominator = (denomPart1) - (denomPart2 * denomPart3);

        double s_param = numerator1 / denominator;
        double t_param = numerator2 / denominator;

//        cout << "\n============ INSIDE TRIANGLE ===========" << endl;
//        cout << "u = [" << u.x << ", " << u.y << ", " << u.z << "]" << endl;
//        cout << "v = [" << v.x << ", " << v.y << ", " << v.z << "]" << endl;
//        cout << "n = [" << n.x << ", " << n.y << ", " << n.z << "]" << endl;
//        cout << "n_norm = [" << n_norm.x << ", " << n_norm.y << ", " << n_norm.z << "]" << endl;
//        cout << "vertex2 = [" << vertex2.x << ", " << vertex2.y << ", " << vertex3.z << "]" << endl;
//        cout << "intersectionPoint = [" << intersectionPoint.x << ", " << intersectionPoint.y << ", "
//             << intersectionPoint.z << "]" << endl;
//        cout << "This number should be 10 ------> " << intersectionPoint.z << endl;
//        cout << "This number should be 10 ------> " << vertex1.z << endl;
//        cout << "This number should be  0 ------> " << intersectionPoint.z - vertex1.z << endl;
//        cout << "w = [" << w.x << ", " << w.y << ", " << w.z << "]" << endl;
//        cout << "s_param = " << s_param << endl;
//        cout << "t_param = " << t_param << endl;

        if(s_param >= 0 && t_param >= 0 && (s_param + t_param) <= 1){ //Clean hit
//            cout << "Clean hit inside triangle." << endl;
            return true;
            //Don't need to set the intersection normal here, b/c Plane::isIntersected() already did that
        } else { //Not in the bounds of the triangle
            return false;
        }
    } else { //Doesn't even intersect with the plane the triangle sits in
        return false;
    }
}

void Triangle::getIntersectionPoint(glm::vec3 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint){
//    camD *= tInters;
//    intersPoint = glm::vec3(camP) + camD;
}

void Triangle::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}
