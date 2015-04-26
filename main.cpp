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
    myE->camPosition = glm::vec3(7.8, 5.0, -12.3);
    myE->intersPoint = glm::vec3(0, 0, 0);
    myE->intersNorm = glm::vec3(0, 0, 0);
    myE->tValue = 40;
    myE->tValueMax = 40;

    //3 point light sources
    myE->pointLight1 = glm::vec3(15, 2, 2); //Front left
    myE->pointLight2 = glm::vec3(17, 6, 0); //Front right
    myE->pointLight3 = glm::vec3(16, 5, 6); //Back right
    myE->pointLight4 = glm::vec3(14, 2, 7); //Back left
    myE->pointLight5 = glm::vec3(15, 4, 4); //Inner Front left
    myE->pointLight6 = glm::vec3(17, 4, 2); //Inner Front right
    myE->pointLight7 = glm::vec3(16, 3, 4); //Inner Back right
    myE->pointLight8 = glm::vec3(14, 4, 5); //Inner Back left
    myE->pointLight9 = glm::vec3(15, 5, 5);  //Inner inner Front left
    myE->pointLight10 = glm::vec3(17, 3, 3); //Inner inner Front right
    myE->pointLight11 = glm::vec3(16, 2, 3); //Inner inner Back right
    myE->pointLight12 = glm::vec3(14, 5, 4); //Inner inner Back left

    //Define our image plane (a.k.a. world window), and our pixel map
    myE->finalImage = new RgbImage("../../../../A3/finalImage.bmp");
    myE->bottomLeftImagePlane = glm::vec3(4.6, 2, -8);
    myE->topRightImagePlane = glm::vec3(8.8, 8, -7);
}

void initializeMyObjects(vector<SceneObject*> &oA){
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
    //For shading
    float myRed = 0;
    float myGreen = 0;
    float myBlue = 0;

    //Because t will change with every intersection, each time it will get "reset"
    double tCopy = myEnv->tValue;
    //And save our current lowest t
    double currentLowestT = tCopy;

    // Make local copies of the image coordinates for simplicity
    // (Otherwise the names are too long)
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
    //glm::vec3 intersNormal(0, 0, 0);

    for(int i = 0/*632*/; i < myRows/*633*/; i++){
        double zOffset = ((double)i / (double)myRows) * zDistance;
        for(int j = 0/*596*/; j < myCols/*598*/; j++){
//            cout << "\nPIXEL whatever ============\n" << endl;
            double yOffset = ((double)j / (double)myCols) * imWidth;
            double xOffset = ((double)i / (double)myRows) * imHeight;
            pixelPosition.x = bCorner.x + xOffset;
            pixelPosition.y = bCorner.y + yOffset;
            pixelPosition.z = bCorner.z + zOffset;

            glm::vec3 rayDirection = pixelPosition - myEnv->camPosition;
            glm::vec3 rayDir3 = glm::normalize(rayDirection);

            vector<SceneObject>::size_type closestObject = 0; //Stores closest object to camera
            bool containsIntersection = false;

            // intersPoint gets set no matter what, even if the new intersection is farther away
            // than an older one. If this happens, we want to revert intersPoint back to its
            // previous value.
            glm::vec3 closestIntersPt = myEnv->intersPoint;

            for(vector<SceneObject>::size_type itr = 0; itr != oArr.size(); itr++){
                if(oArr[itr]->isIntersected(myEnv, rayDir3) == true){
                    containsIntersection = true;
                    if(myEnv->tValue < currentLowestT){
                        currentLowestT = myEnv->tValue;
                        closestIntersPt = myEnv->intersPoint;
                        closestObject = itr;
                    }
                    if(myEnv->tValue > currentLowestT){
                        myEnv->tValue = currentLowestT;
                        myEnv->intersPoint = closestIntersPt;
                    }
                }
                //myEnv->tValue = tCopy; //Reset t
            }
            if(containsIntersection){ //Set the pixel colour of the closest intersected object, if any
                oArr[closestObject]->getColour(myRed, myGreen, myBlue);
                Shading::computeShading(myEnv, oArr, myRed, myGreen, myBlue);
                myEnv->finalImage->SetRgbPixelc(i, j, (char)myRed, (char)myGreen, (char)myBlue);
            }
            currentLowestT = tCopy; //Reset current lowest t
        }
    }
    myEnv->finalImage->WriteBmpFile("../../../../A3/finalImage.bmp");
}

int main(){
    //Create an Environment struct
    Environment *myEnvironment = new Environment;
    initializeMyEnvironment(myEnvironment);

    //Create our object array
    vector<SceneObject*> objectArr;
    initializeMyObjects(objectArr);

    clearImage(myEnvironment->finalImage);
    traversePixels(myEnvironment, objectArr);
}
