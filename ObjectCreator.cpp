#include "ObjectCreator.h"

void ObjectCreator::createScene(Plane *&pF, Plane *&pR, Plane *&pB, Plane *&pL){
    // Scoping these so I can reuse the names
    { // Floor
        glm::vec4 normal( 1,  0,  0, 0); //vector
        glm::vec4 point ( 0,  0,  0, 1); //point
        glm::vec4 min   ( 0,  0,  0, 1); //values
        glm::vec4 max   ( 0, 10, 10, 1); //values
        pF = new Plane(normal, point, min, max, 100, 100, 100);
    }
    { // Right wall
        glm::vec4 normal( 0, -1,  0, 0);
        glm::vec4 point ( 0, 10, 10, 1);
        glm::vec4 min   ( 0, 10,  0, 1);
        glm::vec4 max   (10, 10, 10, 1);
        pR = new Plane(normal, point, min, max, 130, 130, 130);
    }
    { // Back wall
        glm::vec4 normal( 0,  0, -1, 0);
        glm::vec4 point ( 0, 10, 10, 1);
        glm::vec4 min   ( 0,  0, 10, 1);
        glm::vec4 max   (10, 10, 10, 1);
        pB = new Plane(normal, point, min, max, 150, 150, 150);
    }
    { // Left wall
        glm::vec4 normal( 0,  1,  0, 0);
        glm::vec4 point ( 0,  0,  0, 1);
        glm::vec4 min   ( 0,  0,  0, 1);
        glm::vec4 max   (10,  0, 10, 1);
        pL = new Plane(normal, point, min, max, 140, 140, 140);
    }
}

void ObjectCreator::createSpheres(Sphere *&sph1, Sphere *&sph2, Sphere *&sph3, Sphere *&sph4){
    { //Sphere1
        glm::vec4 center(0.0, 2.5, 1.8, 1);
        sph1 = new Sphere(center, 0.8, 95, 77, 104);
    }
    { //Sphere 2
        glm::vec4 center(0.0, 7.2, 1.5, 1);
        sph2 = new Sphere(center, 1.3, 246, 209, 111);
    }
    { //Sphere 3
        glm::vec4 center(0, 3.0, 5.5, 1);
        sph3 = new Sphere(center, 2.3, 230, 73, 95);
    }
    { //Sphere 4
        glm::vec4 center(0, 7.6, 7.8, 1);
        sph4 = new Sphere(center, 2.5, 169, 40, 74);
    }
}

void ObjectCreator::createTriangles(Triangle *&t1, Triangle *&t2, Triangle *&t3){
    { //Triangle 1
        glm::vec4 vertex1(4.0, 1.2, 3.4, 1);
        glm::vec4 vertex2(3.5, 2.8, 4.5, 1);
        glm::vec4 vertex3(5.5, 1.5, 5.1, 1);
        t1 = new Triangle(vertex1, vertex2, vertex3, 0, 240, 0);
    }
    { //Triangle 2
        glm::vec4 vertex1(4.0, 9.4, 1.2, 1);
        glm::vec4 vertex2(7.0, 9.8, 4.6, 1);
        glm::vec4 vertex3(5.0, 9.1, 4.7, 1);
        t2 = new Triangle(vertex1, vertex2, vertex3, 0, 240, 0);
    }
    { //Triangle 3
        glm::vec4 vertex1(0, 0, 0, 1);
        glm::vec4 vertex2(0, 0, 0, 1);
        glm::vec4 vertex3(0, 0, 0, 1);
        t3 = new Triangle(vertex1, vertex2, vertex3, 0, 240, 0);
    }
}
