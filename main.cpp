#include "SceneObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "glm/glm.hpp"

#include <vector>
#include <iostream>
using namespace std;

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

void createScene(Plane *&pF, Plane *&pR, Plane *&pB, Plane *&pL){
    // Create 4 planes. First, the floor:
    { // Scoping these so I can reuse the names
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

int main(){
    //Create the floor and walls
    Plane* pFloor;
    Plane* pRight;
    Plane* pBack;
    Plane* pLeft;
    createScene(pFloor, pRight, pBack, pLeft);

    //Create our 3 triangles
    Triangle* tri1;
    Triangle* tri2;
    Triangle* tri3;
    createTriangles(tri1, tri2, tri3);

    vector<SceneObject*> objectArr;

    //Define our camera position
    glm::vec4 cameraPosition(6, 5, -5, 1);
    //Create our direction vector for each pixel's camera ray
    glm::vec4 cameraDirection(-0.471, 0, 0.882, 1); //Normalized
    double tValue = 40;
    //Create our intersection point
    glm::vec4 intersectionPoint(0, 0, 0, 1);

    /*
    cout << "glm::dot(camera, cameraDir) = "
         << glm::dot(glm::vec3(camera), glm::vec3(cameraDir))
         << endl;
    */

    //Define our 3 point light sources
    glm::vec4 pointLight1(2, 13, 2, 1);
    glm::vec4 pointLight2(7, 13, 9, 1);
    glm::vec4 pointLight3(8, 13, 3, 1);

    /*
    cout << "pFloor->getPointOnPlane().x = " << pFloor->getPointOnPlane().x << endl;
    cout << "pRight->getPointOnPlane().x = " << pRight->getPointOnPlane().x << endl;
    cout << "pBack->getPointOnPlane().x = " << pBack->getPointOnPlane().x << endl;
    cout << "pLeft->getPointOnPlane().x = " << pLeft->getPointOnPlane().x << endl;
    cout << "pFloor = " << pFloor << endl;
    cout << "pRight = " << pRight << endl;
    cout << "pBack = " << pBack << endl;
    cout << "pLeft = " << pLeft << endl;
    */

    //Four spheres           x    y    z   rad
    /*
    Sphere* s1 = new Sphere(0.8, 3.5, 2.8, 0.8);
    Sphere* s2 = new Sphere(1.5, 7.2, 3.5, 2.0);
    Sphere* s3 = new Sphere(1.2, 4.0, 6.5, 2.0);
    Sphere* s4 = new Sphere(2.5, 7.6, 8.3, 2.5);

    objectArr.push_back(s1);
    objectArr.push_back(s2);
    objectArr.push_back(s3);
    objectArr.push_back(s4);
    */

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
