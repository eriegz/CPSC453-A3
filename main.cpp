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
    //For working with pixel colours:
    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    //Because t will change with every intersection, each time it will get "reset"
    double tCopy = t;
    //And save our current lowest t
    double currentLowestT = t;

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

    for(int i = 0/*33*/; i < myRows/*34*/; i++){
        double zOffset = ((double)i / (double)myRows) * zDistance;
        for(int j = 0/*343*/; j < myCols/*344*/; j++){
            double yOffset = ((double)j / (double)myCols) * imWidth;
            double xOffset = ((double)i / (double)myRows) * imHeight;
            pixelPosition.x = bCorner.x + xOffset;
            pixelPosition.y = bCorner.y + yOffset;
            pixelPosition.z = bCorner.z + zOffset;

            glm::vec4 rayDirection = glm::vec4(pixelPosition) - glm::vec4(cPos);
            glm::vec3 rayDir3 = glm::normalize(glm::vec3(rayDirection));

            for(vector<SceneObject>::size_type itr = 0; itr != oArr.size(); itr++){
//                cout << "\nInside main..." << endl;
//                cout << "t = " << t << endl;
//                cout << "currentLowestT = " << currentLowestT << endl;
                if(oArr[itr]->isIntersected(cPos, rayDir3, t, intPoint) == true){
//                    cout << "After isIntersected() is called, t = " << t << endl;
                    if(t < currentLowestT){
//                        cout << t << " is less than " << currentLowestT << "." << endl;
                        oArr[itr]->getColour(myRed, myGreen, myBlue);
                        fImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
                        currentLowestT = t;
                    }
                }
                t = tCopy; //Reset t
            }
            currentLowestT = tCopy; //Reset current lowest t
        }
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
    //Add spheres
    objectArr.push_back(sphere1);
    objectArr.push_back(sphere2);
    objectArr.push_back(sphere3);
    objectArr.push_back(sphere4);
    //Add planes
    objectArr.push_back(pFloor);
    objectArr.push_back(pRight);
    objectArr.push_back(pBack);
    objectArr.push_back(pLeft);
    //Add triangles
//    objectArr.push_back(tri1);
//    objectArr.push_back(tri2);
//    objectArr.push_back(tri3);

    //Define our 3 point light sources
    glm::vec4 pointLight1(2, 13, 2, 1);
    glm::vec4 pointLight2(7, 14, 9, 1);
    glm::vec4 pointLight3(8, 15, 3, 1);

    //Define our camera position, direction, t value, and intersection
    glm::vec4 cameraPosition(7.8, 5.0, -12.3, 1);
    glm::vec4 cameraDirection(-12, 0, 15, 0);
    glm::vec3 cameraDirection3 = glm::normalize(glm::vec3(cameraDirection)); //Normalized
    double tValue = 40;
    glm::vec3 intersectionPoint(0, 0, 0);

    //Set up our image plane, and its bottom Left and top right coordinates
    RgbImage *finalImage = new RgbImage("../../../../A3/finalImage.bmp");
    glm::vec4 bLeftImPlane(4.8, 2, -8, 1);
    glm::vec4 tRightImPlane(8.8, 8, -7, 1);

    //These are the main "go!" functions
    clearImage(finalImage);
    traversePixels(finalImage, bLeftImPlane, tRightImPlane, cameraPosition, tValue, intersectionPoint, objectArr);
}
