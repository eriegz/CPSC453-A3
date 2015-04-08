#define GLM_SWIZZLE

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
    int myRows = fImage->GetNumRows();
    int myCols = fImage->GetNumCols();

    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    for(int i = 0; i < myRows; i++){
        for(int j = 0; j < myCols; j++){
//            fImage->GetRgbPixel(i, j, &myRed, &myGreen, &myBlue);
//            myRed = 0;
//            myGreen = 0;
//            myBlue = 0;
            fImage->SetRgbPixelc(i, j, (char)0, (char)0, (char)0);
        }
    }
    fImage->WriteBmpFile("../../../../A3/finalImage.bmp");
}

void traversePixels(RgbImage *fImage, glm::vec4 bCorner, glm::vec4 tCorner,
                    glm::vec4 cPos, double &t, glm::vec3 &intPoint, vector<SceneObject*> oArr){
    int myRows = fImage->GetNumRows();
    int myCols = fImage->GetNumCols();

    // Create vectors for the other two corners of the image plane to aid with computing
    // its world coordinates.
    glm::vec3 tLeft(tCorner.x, bCorner.y, tCorner.z);
    glm::vec3 bRight(bCorner.x, tCorner.y, bCorner.z);
    double imHeight = glm::length(glm::vec3(tLeft) - glm::vec3(bCorner));
    double imWidth = tCorner.y - bCorner.y;
    double zDistance = tCorner.z - bCorner.z;

    //Store our current ray direction and its position on the image plane
    //rayDirection(0, 0, 0, 0);
    glm::vec4 pixelPosition(0, 0, 0, 1);

    unsigned char myColour;

    for(int i = 0; i < myRows; i++){
        //Every row, the z value will change slightly. This variable will store that value:
        double zOffset = ((double)i / (double)myRows) * zDistance;
        for(int j = 0; j < myCols; j++){
            double yOffset = ((double)j / (double)myCols) * imWidth;
            double xOffset = ((double)i / (double)myRows) * imHeight;
            pixelPosition.x = bCorner.x + xOffset;
            pixelPosition.y = bCorner.y + yOffset;
            pixelPosition.z = bCorner.z + zOffset;
            glm::vec4 rayDirection = glm::vec4(cPos) - glm::vec4(pixelPosition);
            glm::vec3 rayDir3 = glm::normalize(glm::vec3(rayDirection));
            cout << "Shooting ray (" << rayDir3.x << ", "
                 << rayDir3.y << ", " << rayDir3.z << ")"
                 << "          i = " << i << ", j = " << j << endl;
            for(vector<SceneObject>::size_type itr = 0; itr != oArr.size(); itr++){
                if(oArr[itr]->isIntersected(cPos, rayDir3, t, intPoint) == true){
                    // /*unsigned char */myColour = oArr[itr]->getColour();
                    //fImage->SetRgbPixelc(i, j, (char)myColour, (char)myColour, (char)myColour);
                    fImage->SetRgbPixelc(i, j, (char)255, (char)255, (char)255);
                    break;
                }
            }
            //Set rayDirection through pixel
            //fImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
        }
        //cout << "Received colour " << (int)myColour << endl;
    }
    fImage->WriteBmpFile("../../../../A3/finalImage.bmp");
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
//    objectArr.push_back(pFloor);
//    objectArr.push_back(pRight);
//    objectArr.push_back(pBack);
//    objectArr.push_back(pLeft);
    //Add spheres
    objectArr.push_back(sphere1);
//    objectArr.push_back(sphere2);
//    objectArr.push_back(sphere3);
//    objectArr.push_back(sphere4);
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
    glm::vec4 cameraDirection(-0.471, 0, 0.882, 0); //Normalized
    glm::vec3 cameraDirection3(cameraDirection);
    double tValue = 40;
    glm::vec3 intersectionPoint(0, 0, 0);

    //Set up our image plane, and its bottom Left and top right coordinates
    RgbImage *finalImage = new RgbImage("../../../../A3/finalImage.bmp");
    glm::vec4 bLeftImPlane(3, 2, -3, 1);
    glm::vec4 tRightImPlane(7, 8, -2, 1);

    clearImage(finalImage);
    traversePixels(finalImage, bLeftImPlane, tRightImPlane, cameraPosition, tValue, intersectionPoint, objectArr);

    //Iterate through our scene objects
    //vector<SceneObject*>::iterator itr;

    // ========== TEST SECTION ==============
    //pBack->isIntersected(cameraPosition, cameraDirection3, tValue, intersectionPoint);
    //pBack->isIntersected2(camera, cameraDir, tValue);
//    glm::vec3 normalizationTest(5, 2, 6);
//    glm::vec3 normalizedVector = glm::normalize(normalizationTest);
//    cout << "normalizationTest = (" << normalizedVector.x << ", " << normalizedVector.y
//         << ", " << normalizedVector.z << ")" << endl;

    /*
    glm::vec4 testSphereC(0, 5, 5, 1);
    Sphere* testSphere = new Sphere(testSphereC, 2);
    glm::vec4 testCameraPosition(0, 5, -5, 1);
    glm::vec4 testCameraDirection(0, 0, 1, 0); //Normalized
    testSphere->isIntersected(testCameraPosition, testCameraDirection, tValue, intersectionPoint);
    cout << "intersectionPoint:" << endl
         << "  " << intersectionPoint.x
         << "  " << intersectionPoint.y
         << "  " << intersectionPoint.z << endl;
    //*/
//    cout << "No immediately-visible problems." << endl;
}
