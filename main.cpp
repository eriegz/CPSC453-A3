#define GLM_SWIZZLE

#include "SceneObject.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "RgbImage.h"
#include "ObjectCreator.h"
#include "Shading.h"
#include "Environment.h"

#include "glm/glm.hpp"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

void initializeMyEnvironment(Environment *myE){
    //Camera, intersection point
    myE->camPosition = glm::vec3(7.8, 5.0, -12.3);;
//    myE->camDirection = glm::vec3(-12, 0, 15);
    myE->intersPoint = glm::vec3(0, 0, 0);
    myE->intersNorm = glm::vec3(0, 0, 0);
    myE->tValue = 40;

    //3 point light sources
    myE->pointLight1 = glm::vec3(13, 2, 2);
    myE->pointLight2 = glm::vec3(14, 7, 9);
    myE->pointLight3 = glm::vec3(15, 8, 3);

    //Image plane
    myE->finalImage = new RgbImage("../../../../A3/finalImage.bmp");
    myE->bottomLeftImagePlane = glm::vec3(4.6, 2, -8);
    myE->topRightImagePlane = glm::vec3(8.8, 8, -7);
}

void initializeMyObjects(){

}

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

//void traversePixels(RgbImage *fImage, glm::vec3 bCorner, glm::vec3 tCorner,
//                    glm::vec3 cPos, double &t, glm::vec3 &intersPoint, vector<SceneObject*> oArr)

void traversePixels(Environment *myEnv, vector<SceneObject*> oArr){
    int myRows = myEnv->finalImage->GetNumRows();
    int myCols = myEnv->finalImage->GetNumCols();
    //For working with pixel colours:
    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    //Because t will change with every intersection, each time it will get "reset"
    double tCopy = myEnv->tValue;
    //And save our current lowest t
    double currentLowestT = tCopy;

    // Make local copies of the image coordinates for simplicity
    glm::vec3 tCorner = myEnv->topRightImagePlane;
    glm::vec3 bCorner = myEnv->bottomLeftImagePlane;
    glm::vec3 tLeft(tCorner.x, bCorner.y, tCorner.z); //Then a vec3 for one more corner, to help
    double imHeight = glm::length(glm::vec3(tLeft) - glm::vec3(myEnv->bottomLeftImagePlane));
    double imWidth = myEnv->topRightImagePlane.y - myEnv->bottomLeftImagePlane.y;
    double zDistance = myEnv->topRightImagePlane.z - myEnv->bottomLeftImagePlane.z;

    //Store our current ray direction and its position on the image plane
    //rayDirection(0, 0, 0, 0);
    glm::vec3 pixelPosition(0, 0, 0);

    //Store the normal of our ray intersection
    glm::vec3 intersNormal(0, 0, 0);

    for(int i = 0/*712*/; i < myRows/*713*/; i++){
        double zOffset = ((double)i / (double)myRows) * zDistance;
        for(int j = 0/*600*/; j < myCols/*601*/; j++){
            double yOffset = ((double)j / (double)myCols) * imWidth;
            double xOffset = ((double)i / (double)myRows) * imHeight;
            pixelPosition.x = bCorner.x + xOffset;
            pixelPosition.y = bCorner.y + yOffset;
            pixelPosition.z = bCorner.z + zOffset;

            glm::vec3 rayDirection = pixelPosition - myEnv->camPosition;
            glm::vec3 rayDir3 = glm::normalize(rayDirection);

            for(vector<SceneObject>::size_type itr = 0; itr != oArr.size(); itr++){
//                cout << "\nInside main..." << endl;
//                cout << "t = " << t << endl;
//                cout << "currentLowestT = " << currentLowestT << endl;
                if(oArr[itr]->isIntersected(myEnv, rayDir3) == true){
//                    cout << "============SUCCESSFUL INTERSECTION============" << endl;
//                    cout << "After isIntersected() is called, myEnv->tValue = " << myEnv->tValue << endl;
//                    cout << "And currentLowestT = " << currentLowestT << endl;
                    if(myEnv->tValue < currentLowestT){
//                        cout << myEnv->tValue << " is less than " << currentLowestT << "." << endl;
                        oArr[itr]->getColour(myRed, myGreen, myBlue);
//                        Shading::computeShading(intersPoint, intersNormal, pointLight1, pointLight2, pointLight3,
//                                                oArr, myRed, myGreen, myBlue);
                        myEnv->finalImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
                        currentLowestT = myEnv->tValue;
                    }
                }
                myEnv->tValue = tCopy; //Reset t
            }
            currentLowestT = tCopy; //Reset current lowest t
        }
    }
    myEnv->finalImage->WriteBmpFile("../../../../A3/finalImage.bmp");
}

int main(){
    Environment *myEnvironment = new Environment;
    initializeMyEnvironment(myEnvironment);
    initializeMyObjects();

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
    ObjectCreator::createTriangles(tri1, tri2, tri3);

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
    objectArr.push_back(tri1);
    objectArr.push_back(tri2);
    objectArr.push_back(tri3);

//    //Define our camera position, direction, t value, and intersection
//    glm::vec3 cameraPosition(7.8, 5.0, -12.3);
//    glm::vec3 cameraDirection(-12, 0, 15);
//    glm::vec3 cameraDirection3 = glm::normalize(glm::vec3(cameraDirection)); //Normalized
//    double tValue = 40;
//    glm::vec3 intersectionPoint(0, 0, 0);

//    //Set up our image plane, and its bottom Left and top right coordinates
//    RgbImage *finalImage = new RgbImage("../../../../A3/finalImage.bmp");
//    glm::vec3 bLeftImPlane(4.6, 2, -8);
//    glm::vec3 tRightImPlane(8.8, 8, -7);

    //These are the main "go!" functions
    clearImage(myEnvironment->finalImage);
    traversePixels(myEnvironment, objectArr);
    //traversePixels(finalImage, bLeftImPlane, tRightImPlane, cameraPosition, tValue, intersectionPoint, objectArr);
}
