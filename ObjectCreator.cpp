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
        glm::vec4 center(5, 1, 1.8, 1);
        sph1 = new Sphere(center, 1.1, 255, 196, 0);
    }
    { //Sphere 2
        glm::vec4 center(3, 7.2, 1.5, 1);
        sph2 = new Sphere(center, 1.3, 0, 230, 4);
    }
    { //Sphere 3
        glm::vec4 center(0, 3.0, 5.5, 1);
        sph3 = new Sphere(center, 2.3, 219, 33, 25);
    }
    { //Sphere 4
        glm::vec4 center(0, 7.6, 7.8, 1);
        sph4 = new Sphere(center, 5, 0, 118, 255);
    }
}

void ObjectCreator::createTriangles(Triangle *&t1, Triangle *&t2, Triangle *&t3){
    { //Triangle 1
        glm::vec3 vertex1(9, 5.5, 6.5);
        glm::vec3 vertex2(7.5, 2.2, 8);
        glm::vec3 vertex3(7.1, 4.8, 5.1);
        t1 = new Triangle(vertex1, vertex2, vertex3, 212, 0, 174);
    }
    { //Triangle 2
        glm::vec3 vertex1(7.1, 4.8, 5.1);
        glm::vec3 vertex2(7.5, 2.2, 8);
        glm::vec3 vertex3(5.3, 5.1, 8.2);
        t2 = new Triangle(vertex1, vertex2, vertex3, 163, 0, 134);
    }
    { //Triangle 3
        glm::vec3 vertex1(9, 5.5, 6.5);
        glm::vec3 vertex2(7.1, 4.8, 5.1);
        glm::vec3 vertex3(5.3, 5.1, 8.2);
        t3 = new Triangle(vertex1, vertex2, vertex3, 110, 0, 91);
    }
}
