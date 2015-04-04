#include "SceneObject.h"
#include "Sphere.h"
#include "Plane.h"
#include "glm/glm.hpp"

#include <vector>
#include <iostream>
using namespace std;

void createScene(Plane* pF, Plane* pR, Plane* pB, Plane* pL){
    // Create 4 planes. First, the floor:
    { //Scoped so that I can reuse 'v1, v2...' etc.
        glm::vec4 v1( 0,  0,  0, 1);
        glm::vec4 v2( 0, 10,  0, 1);
        glm::vec4 v3( 0, 10, 10, 1);
        glm::vec4 v4( 0,  0, 10, 1);
        pF = new Plane(v1, v2, v3, v4);
    }
    { // Right wall
        glm::vec4 v1(10, 10,  0, 1);
        glm::vec4 v2(10, 10, 10, 1);
        glm::vec4 v3( 0, 10, 10, 1);
        glm::vec4 v4( 0, 10,  0, 1);
        pR = new Plane(v1, v2, v3, v4);
    }
    { // Back wall
        glm::vec4 v1( 0,  0, 10, 1);
        glm::vec4 v2( 0, 10, 10, 1);
        glm::vec4 v3(10, 10, 10, 1);
        glm::vec4 v4(10,  0, 10, 1);
        pB = new Plane(v1, v2, v3, v4);
    }
    { // Left wall
        glm::vec4 v1( 0,  0,  0, 1);
        glm::vec4 v4( 0,  0, 10, 1);
        glm::vec4 v3(10,  0, 10, 1);
        glm::vec4 v2(10,  0,  0, 1);
        pL = new Plane(v1, v2, v3, v4);
    }
}

int main(){
    vector<SceneObject*> objectArr;

    //Create the floor and walls
    Plane* pFloor = NULL;
    Plane* pRight = NULL;
    Plane* pBack = NULL;
    Plane* pLeft = NULL;
    createScene(pFloor, pRight, pBack, pLeft);

    //Four spheres           x    y    z   rad
    Sphere* s1 = new Sphere(0.8, 3.5, 2.8, 0.8);
    Sphere* s2 = new Sphere(1.5, 7.2, 3.5, 2.0);
    Sphere* s3 = new Sphere(1.2, 4.0, 6.5, 2.0);
    Sphere* s4 = new Sphere(2.5, 7.6, 8.3, 2.5);

    objectArr.push_back(s1);
    objectArr.push_back(s2);
    objectArr.push_back(s3);
    objectArr.push_back(s4);

    vector<SceneObject*>::iterator i;

    for(vector<SceneObject>::size_type i = 0; i != objectArr.size(); i++){
        objectArr[i]->isIntersected();
    }
}
