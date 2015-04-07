#include "SceneObject.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "RgbImage.h"

#include "glm/glm.hpp"

#include <vector>
#include <iostream>
using namespace std;

void createScene(Plane *&pF, Plane *&pR, Plane *&pB, Plane *&pL){
    // Scoping these so I can reuse the names
    { // Floor
        glm::vec4 normal( 1,  0,  0, 0); //vector
        glm::vec4 point ( 0,  0,  0, 1); //point
        glm::vec4 min   ( 0,  0,  0, 1); //values
        glm::vec4 max   ( 0, 10, 10, 1); //values
        pF = new Plane(normal, point, min, max);
    }

    { // Right wall
        glm::vec4 normal( 0, -1,  0, 0);
        glm::vec4 point ( 0, 10, 10, 1);
        glm::vec4 min   ( 0,  0,  0, 1);
        glm::vec4 max   (10,  0, 10, 1);
        pR = new Plane(normal, point, min, max);
    }
    { // Back wall
        glm::vec4 normal( 0,  0, -1, 0);
        glm::vec4 point ( 0, 10, 10, 1);
        glm::vec4 min   ( 0,  0,  0, 1);
        glm::vec4 max   (10, 10,  0, 1);
        pB = new Plane(normal, point, min, max);
    }
    { // Left wall
        glm::vec4 normal( 0,  1,  0, 0);
        glm::vec4 point ( 0,  0,  0, 1);
        glm::vec4 min   ( 0,  0,  0, 1);
        glm::vec4 max   (10,  0, 10, 1);
        pL = new Plane(normal, point, min, max);
    }
}

void createSpheres(Sphere *&sph1, Sphere *&sph2, Sphere *&sph3, Sphere *&sph4){
    { //Sphere1
        glm::vec4 center(0.8, 3.5, 2.8, 1);
        sph1 = new Sphere(center, 0.8);
    }
    { //Sphere 2
        glm::vec4 center(1.5, 7.2, 3.5, 1);
        sph2 = new Sphere(center, 2.0);
    }
    { //Sphere 3
        glm::vec4 center(1.2, 4.0, 6.5, 1);
        sph3 = new Sphere(center, 2.3);
    }
    { //Sphere 4
        glm::vec4 center(2.5, 7.6, 7.8, 2.5);
        sph4 = new Sphere(center, 2.5);
    }
}

void createTriangles(Triangle *&t1, Triangle *&t2, Triangle *&t3){
    { //Triangle 1
        glm::vec4 vertex1(4.0, 1.2, 3.4, 1);
        glm::vec4 vertex2(3.5, 2.8, 4.5, 1);
        glm::vec4 vertex3(5.5, 1.5, 5.1, 1);
        t1 = new Triangle(vertex1, vertex2, vertex3);
    }
    { //Triangle 2
        glm::vec4 vertex1(4.0, 9.4, 1.2, 1);
        glm::vec4 vertex2(7.0, 9.8, 4.6, 1);
        glm::vec4 vertex3(5.0, 9.1, 4.7, 1);
        t2 = new Triangle(vertex1, vertex2, vertex3);
    }
    { //Triangle 3
        glm::vec4 vertex1(0, 0, 0, 1);
        glm::vec4 vertex2(0, 0, 0, 1);
        glm::vec4 vertex3(0, 0, 0, 1);
        t3 = new Triangle(vertex1, vertex2, vertex3);
    }
}

int main(){
    //Create the floor and walls
    Plane* pFloor;
    Plane* pRight;
    Plane* pBack;
    Plane* pLeft;
    createScene(pFloor, pRight, pBack, pLeft);

    //Create our 4 spheres
    Sphere* sphere1;
    Sphere* sphere2;
    Sphere* sphere3;
    Sphere* sphere4;
    createSpheres(sphere1, sphere2, sphere3, sphere4);

    //Create our 3 triangles
    Triangle* tri1;
    Triangle* tri2;
    Triangle* tri3;
    createTriangles(tri1, tri2, tri3);

    vector<SceneObject*> objectArr;
    //Add planes
    objectArr.push_back(pFloor);
    objectArr.push_back(pRight);
    objectArr.push_back(pBack);
    objectArr.push_back(pLeft);
    //Add triangles
    objectArr.push_back(tri1);
    objectArr.push_back(tri2);
    objectArr.push_back(tri3);
    //Add spheres
    objectArr.push_back(sphere1);
    objectArr.push_back(sphere2);
    objectArr.push_back(sphere3);
    objectArr.push_back(sphere4);

    //Define our 3 point light sources
    glm::vec4 pointLight1(2, 13, 2, 1);
    glm::vec4 pointLight2(7, 13, 9, 1);
    glm::vec4 pointLight3(8, 13, 3, 1);

    //Define our camera position
    glm::vec4 cameraPosition(6, 5, -5, 1);
    //Create our direction vector for each pixel's camera ray
    glm::vec4 cameraDirection(-0.471, 0, 0.882, 1); //Normalized
    double tValue = 40;
    //Create our intersection point
    glm::vec4 intersectionPoint(0, 0, 0, 1);

    //Iterate through our scene objects
    vector<SceneObject*>::iterator i;
    for(vector<SceneObject>::size_type i = 0; i != objectArr.size(); i++){
        //objectArr[i]->isIntersected();
    }

    // ========== TEST SECTION ==============
    pBack->isIntersected(cameraPosition, cameraDirection, tValue, intersectionPoint);
    //pBack->isIntersected2(camera, cameraDir, tValue);

    /*
    glm::vec4 testSphereC(0, 5, 5, 1);
    Sphere* testSphere = new Sphere(testSphereC, 2);
    glm::vec4 testCameraPosition(0, 5, -5, 1);
    glm::vec4 testCameraDirection(0, 0, 1, 1); //Normalized
    testSphere->isIntersected(testCameraPosition, testCameraDirection, tValue, intersectionPoint);
    cout << "intersectionPoint:" << endl
         << "  " << intersectionPoint.x
         << "  " << intersectionPoint.y
         << "  " << intersectionPoint.z << endl;
    //*/
    cout << "No immediately-visible problems." << endl;
}
