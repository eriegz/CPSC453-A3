#include "Reflection.h"

void Reflection::computeReflection(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB, double kS){
    // For reflection computation, the same intersection calculations will be performed as in
    // shading, except now if we get an intersection, instead of darkening the myR, myG, and myB,
    // we will blend them with the colour of what we hit.

    // Save copies of everything
    glm::vec3 camPosition_Backup = myEnv->camPosition;
    glm::vec3 camDirection_Backup = myEnv->camDirection;
    glm::vec3 intersPoint_Backup = myEnv->intersPoint;
    glm::vec3 intersNorm_Backup = myEnv->intersNorm;
    double tValueMax_Backup = myEnv->tValueMax;
    double currentLowestT = tValueMax_Backup;

    // Now, just as before, our camera position will now become our intersection point
    myEnv->camPosition = myEnv->intersPoint;
    // And our camDirection will now become the reflected camDirection ray
    glm::vec3 reflectedRay = reflect(camDirection_Backup, intersNorm_Backup);
    //myEnv->camDirection = glm::normalize(reflectedRay);

    // ===== Closest intersection calculation =====
    vector<SceneObject>::size_type closestObject = 0; //Stores closest object to camera
    bool containsIntersection = false;
    glm::vec3 closestIntersPt = myEnv->intersPoint;
    // ======================================
    for(vector<SceneObject>::size_type itr = 0; itr != oA.size(); itr++){ //Traverse all scene objects
        if(oA[itr]->isIntersected(myEnv, reflectedRay) == true){ //Current object in shadow
            // ===== Closest shadow calculation =====
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
            // ======================================
        }
    } //We now have the closest intersection

    if(containsIntersection){ //Reflection
        oA[closestObject]->getColour(myR, myG, myB);

        //myR *= shadowAttn; myG *= shadowAttn; myB *= shadowAttn; //Darken all the colours a bit, for now
    }
    myEnv->camPosition = camPosition_Backup; //Reset values
    myEnv->camDirection = camDirection_Backup;
    myEnv->intersPoint = intersPoint_Backup;
}

