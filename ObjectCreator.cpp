#include "ObjectCreator.h"

void ObjectCreator::createScene(Plane *&pF, Plane *&pR, Plane *&pB, Plane *&pL){
    // Scoping these so I can reuse the names
    { // Floor
        glm::vec3 normal( 1,  0,  0);
        glm::vec3 point ( 0,  0,  0);
        glm::vec3 min   ( 0,  0,  0);
        glm::vec3 max   ( 0, 10, 10);
        pF = new Plane(normal, point, min, max, 160, 160, 160);
    }
    { // Right wall
        glm::vec3 normal( 0, -1,  0);
        glm::vec3 point ( 0, 10, 10);
        glm::vec3 min   ( 0, 10,  0);
        glm::vec3 max   (10, 10, 10);
        pR = new Plane(normal, point, min, max, 120, 120, 120);
    }
    { // Back wall
        glm::vec3 normal( 0,  0, -1);
        glm::vec3 point ( 0, 10, 10);
        glm::vec3 min   ( 0,  0, 10);
        glm::vec3 max   (10, 10, 10);
        pB = new Plane(normal, point, min, max, 140, 140, 140);
    }
    { // Left wall
        glm::vec3 normal( 0,  1,  0);
        glm::vec3 point ( 0,  0,  0);
        glm::vec3 min   ( 0,  0,  0);
        glm::vec3 max   (10,  0, 10);
        pL = new Plane(normal, point, min, max, 130, 130, 130);
    }
}

void ObjectCreator::createSpheres(Sphere *&sph1, Sphere *&sph2, Sphere *&sph3, Sphere *&sph4){
    { //Sphere1
        glm::vec4 center(6, 0.3, 3, 1);
        sph1 = new Sphere(center, 2.1, 255, 196, 0);
    }
    { //Sphere 2
        glm::vec4 center(4.2, 7.2, 1.7, 1);
        sph2 = new Sphere(center, 1.3, 0, 230, 4);
    }
    { //Sphere 3
        glm::vec4 center(0, 3.5, 6, 1);
        sph3 = new Sphere(center, 2.3, 219, 33, 25);
    }
    { //Sphere 4
        glm::vec4 center(0, 8, 8.2, 1);
        sph4 = new Sphere(center, 5, 0, 118, 255);
    }
}

void ObjectCreator::createTriangles(Triangle *&t1, Triangle *&t2, Triangle *&t3, Triangle *&t4){
    { //Triangle 1
        glm::vec3 vertex1(10.5, 5, 5.5);
        glm::vec3 vertex2(7.6, 2.4, 7.2);
        glm::vec3 vertex3(7.8, 5.2, 4.1);
        t1 = new Triangle(vertex1, vertex2, vertex3, 212, 0, 174);
    }
    { //Triangle 2
        glm::vec3 vertex1(7.8, 5.2, 4.1);
        glm::vec3 vertex2(7.6, 2.4, 7.2);
        glm::vec3 vertex3(6.9, 6.1, 8.4);
        t2 = new Triangle(vertex1, vertex2, vertex3, 212, 0, 174);
    }
    { //Triangle 3
        glm::vec3 vertex1(10.5, 5, 5.5);
        glm::vec3 vertex2(7.8, 5.2, 4.1);
        glm::vec3 vertex3(6.9, 6.1, 8.4);
        t3 = new Triangle(vertex1, vertex2, vertex3, 212, 0, 174);
    }
    { //Triangle 4
        glm::vec3 vertex1(10.5, 5, 5.5);
        glm::vec3 vertex2(6.9, 6.1, 8.4);
        glm::vec3 vertex3(7.6, 2.4, 7.2);
        t4 = new Triangle(vertex1, vertex2, vertex3, 212, 0, 174);
    }
}

void ObjectCreator::initializeMyObjects(vector<SceneObject*> &oA){
    //Create the floor and walls
    Plane* pFloor;
    Plane* pRight;
    Plane* pBack;
    Plane* pLeft;
    ObjectCreator::createScene(pFloor, pRight, pBack, pLeft);

    //Create our 4 spheres
    Sphere* sphere1;
    Sphere* sphere2;
    Sphere* sphere3;
    Sphere* sphere4;
    ObjectCreator::createSpheres(sphere1, sphere2, sphere3, sphere4);

    //Create our 3 triangles
    Triangle* tri1;
    Triangle* tri2;
    Triangle* tri3;
    Triangle* tri4;
    ObjectCreator::createTriangles(tri1, tri2, tri3, tri4);

    //Add spheres
    oA.push_back(sphere1);
    oA.push_back(sphere2);
    oA.push_back(sphere3);
    oA.push_back(sphere4);
    //Add planes
    oA.push_back(pFloor);
    oA.push_back(pRight);
    oA.push_back(pBack);
    oA.push_back(pLeft);
    //Add triangles
    oA.push_back(tri1);
    oA.push_back(tri2);
    oA.push_back(tri3);
    oA.push_back(tri4);
}
