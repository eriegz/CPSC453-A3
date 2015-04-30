#ifndef SHADING_H
#define SHADING_H

#include <vector>
#include <iostream>
using namespace std;

#include "SceneObject.h"
#include "glm/glm.hpp"

class Shading{
public:
    void static computeShading(Environment*, vector<SceneObject*>, float &, float &, float &, double, double);
    void static calculateShadow();
};

#endif // SHADING_H
