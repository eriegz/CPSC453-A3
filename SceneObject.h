#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>
using namespace std;

class SceneObject{
public:
    virtual bool isIntersected() = 0;
    //virtual string getObjectType();
};

#endif // SCENEOBJECT_H
