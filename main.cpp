#include "SceneObject.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "RgbImage.h"
#include "ObjectCreator.h"

#include "glm/glm.hpp"

//#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

void clearImage(RgbImage *fImage){
    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    //Delete these two:
    int myRows = 0;
    int myCols = 0;

    for(int i = 0; i < myRows; i++){
        for(int j = 0; j < myCols; j++){
//            fImage->GetRgbPixel(i, j, &myRed, &myGreen, &myBlue);
//            myRed = 0;
//            myGreen = 0;
//            myBlue = 0;
            fImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
        }
    }
}

void traversePixels(RgbImage *fImage, long rows, long cols, glm::vec4 vec1,  glm::vec4 vec2, glm::vec4 vec3){
    //Delete these 3:
    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
//            fImage->GetRgbPixel(i, j, &myRed, &myGreen, &myBlue);
//            myRed = 0;
//            myGreen = 0;
//            myBlue = 0;
            fImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
        }
    }
}

int main(){
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
//    Triangle* tri1;
//    Triangle* tri2;
//    Triangle* tri3;
//    ObjectCreator::createTriangles(tri1, tri2, tri3);

    vector<SceneObject*> objectArr;
    //Add planes
    objectArr.push_back(pFloor);
    objectArr.push_back(pRight);
    objectArr.push_back(pBack);
    objectArr.push_back(pLeft);
    //Add spheres
    objectArr.push_back(sphere1);
    objectArr.push_back(sphere2);
    objectArr.push_back(sphere3);
    objectArr.push_back(sphere4);
    //Add triangles
//    objectArr.push_back(tri1);
//    objectArr.push_back(tri2);
//    objectArr.push_back(tri3);

    //Define our 3 point light sources
    glm::vec4 pointLight1(2, 13, 2, 1);
    glm::vec4 pointLight2(7, 14, 9, 1);
    glm::vec4 pointLight3(8, 15, 3, 1);

    //Define our camera position, direction, t value, and intersection
    glm::vec4 cameraPosition(6, 5, -5, 1);
    glm::vec4 cameraDirection(-0.471, 0, 0.882, 1); //Normalized
    double tValue = 40;
    glm::vec4 intersectionPoint(0, 0, 0, 1);

    //Set up our image plane, and its bottom Left and top right coordinates
    RgbImage *finalImage = new RgbImage("../../../../A3/finalImage.bmp");
    glm::vec4 bLeftImPlane(3, 2, -3, 1);
    glm::vec4 tRightImPlane(7, 8, -4, 1);
    long myRows = finalImage->GetNumRows();
    long myCols = finalImage->GetNumCols();
    traversePixels(finalImage, myRows, myCols, bLeftImPlane, tRightImPlane, cameraPosition);

    clearImage(finalImage);
    finalImage->WriteBmpFile("../../../../A3/finalImage.bmp");

    //Iterate through our scene objects
    vector<SceneObject*>::iterator i;
    for(vector<SceneObject>::size_type i = 0; i != objectArr.size(); i++){
        //objectArr[i]->isIntersected();
    }

    // ========== TEST SECTION ==============
    pBack->isIntersected(cameraPosition, cameraDirection, tValue, intersectionPoint);
    //pBack->isIntersected2(camera, cameraDir, tValue);

    //*
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
//    cout << "No immediately-visible problems." << endl;
}
