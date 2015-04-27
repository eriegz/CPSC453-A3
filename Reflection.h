#ifndef REFLECTION_H
#define REFLECTION_H

#include <vector>
#include <iostream>
using namespace std;

#include "SceneObject.h"
#include "glm/glm.hpp"

class Reflection{
public:
    void static computeReflection(Environment*, vector<SceneObject*>, float &, float &, float &, double);
};

#endif // REFLECTION_H
