#include "Sphere.h"

Sphere::Sphere(double rad, double x, double y, double z){
    radius = rad;
    xCoor = x;
    yCoor = y;
    zCoor = z;
}

bool Sphere::isIntersected(glm::vec4 cam, glm::vec4 camDir, double &t){
    if(1 < 2)
        return true;
    else
        return false;
}

double Sphere::getRadius(){return this->radius;}
double Sphere::getX(){return this->xCoor;}
double Sphere::getY(){return this->yCoor;}
double Sphere::getZ(){return this->zCoor;}
