#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "RgbImage.h"

// This struct will hold all of the things about the scene that aren't objects
// (i.e.: camera direction, image frame, lights, etc.)
struct Environment{
    //Camera, intersection, etc.
    glm::vec3 camPosition;
    glm::vec3 camDirection;
    glm::vec3 intersPoint;
    glm::vec3 intersNorm;
    double tValue;
    double tValueMax;

    //Point lights
    glm::vec3 pointLight1;
    glm::vec3 pointLight2;
    glm::vec3 pointLight3;
    glm::vec3 pointLight4;
    glm::vec3 pointLight5;
    glm::vec3 pointLight6;
    glm::vec3 pointLight7;
    glm::vec3 pointLight8;
    glm::vec3 pointLight9;
    glm::vec3 pointLight10;
    glm::vec3 pointLight11;
    glm::vec3 pointLight12;

    //Image plane
    RgbImage *finalImage;
    glm::vec3 bottomLeftImagePlane;
    glm::vec3 topRightImagePlane;
} /*myEnvironment*/;

#endif // ENVIRONMENT
