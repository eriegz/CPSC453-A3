#ifndef ENVIRONMENT
#define ENVIRONMENT

#define GLM_SWIZZLE

#include "glm/glm.hpp"
#include "RgbImage.h"

#include <vector>
#include <iostream>
using namespace std;

class Environment{
public:
    Environment(){}
    void initializeMyEnvironment();

    //Camera, intersection, etc.
    glm::vec3 camPosition;
    glm::vec3 camDirection;
    glm::vec3 intersPoint;
    glm::vec3 intersNorm;
    double tValue;
    double tValueMax;
    int reflectionDepth;
    double kAmbient; //Global Phong variable

    //Point lights
    vector<glm::vec3> lightSources;
    vector<glm::vec3> lightColours;

    //Image plane
    RgbImage *finalImage;
    glm::vec3 bottomLeftImagePlane;
    glm::vec3 topRightImagePlane;
};

#endif // ENVIRONMENT
