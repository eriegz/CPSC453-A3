#include "Triangle.h"

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, long red, long green, long blue){
    vertex1 = v1;
    vertex2 = v2;
    vertex3 = v3;
    redC = red;
    greenC = green;
    blueC = blue;
}

bool Triangle::isIntersected(glm::vec4 camPos, glm::vec3 camDir, double &t, glm::vec3 &intersectionPoint){
//    Vector    u, v, n;              // triangle vectors
//    Vector    dir, w0, w;           // ray vectors
//    float     r, a, b;              // params to calc ray-plane intersect

//    // get triangle edge vectors and plane normal
//    u = T.V1 - T.V0;
//    v = T.V2 - T.V0;
//    n = u * v;              // cross product
//    if (n == (Vector)0)             // triangle is degenerate
//        return -1;                  // do not deal with this case

//    dir = R.P1 - R.P0;              // ray direction vector
//    w0 = R.P0 - T.V0;
//    a = -dot(n,w0);
//    b = dot(n,dir);
//    if (fabs(b) < SMALL_NUM) {     // ray is  parallel to triangle plane
//        if (a == 0)                 // ray lies in triangle plane
//            return 2;
//        else return 0;              // ray disjoint from plane
//    }

//    // get intersect point of ray with triangle plane
//    r = a / b;
//    if (r < 0.0)                    // ray goes away from triangle
//        return 0;                   // => no intersect
//    // for a segment, also test if (r > 1.0) => no intersect

//    *I = R.P0 + r * dir;            // intersect point of ray and plane

//    // is I inside T?
//    float    uu, uv, vv, wu, wv, D;
//    uu = dot(u,u);
//    uv = dot(u,v);
//    vv = dot(v,v);
//    w = *I - T.V0;
//    wu = dot(w,u);
//    wv = dot(w,v);
//    D = uv * uv - uu * vv;

//    // get and test parametric coords
//    float s, t;
//    s = (uv * wv - vv * wu) / D;
//    if (s < 0.0 || s > 1.0)         // I is outside T
//        return 0;
//    t = (uv * wu - uu * wv) / D;
//    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
//        return 0;

    return true;                       // I is in T
}

void Triangle::getIntersectionPoint(glm::vec4 camP, glm::vec3 camD, double tInters, glm::vec3 &intersPoint){
    camD *= tInters;
    intersPoint = glm::vec3(camP) + camD;
}

void Triangle::getColour(float &myR, float &myG, float &myB){
    myR = redC;
    myG = greenC;
    myB = blueC;
}
