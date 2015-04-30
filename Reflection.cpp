#include "Reflection.h"

void Reflection::computeReflection(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB, double kS){
    // For reflection computation, the same intersection calculations will be performed as in
    // shading, except now if we get an intersection, instead of darkening the myR, myG, and myB,
    // we will blend them with the colour of what we hit.

    if((myR == 0 && myG == 118 && myB == 255) ||
       (myR == 0 && myG == 230 && myB == 4))
        return;

    // First of all, if the current object isn't reflective, then skip this entire function
    if(kS == 0)
        return;

    // Stopping condition, as this function will be called recursively
    if(myEnv->reflectionDepth == 0)
        return;

    // Save copies of everything
    myEnv->camDirection = glm::normalize(myEnv->intersPoint - myEnv->camPosition);
    glm::vec3 camDirection_Backup = myEnv->camDirection;
    glm::vec3 camPosition_Backup = myEnv->camPosition;
    glm::vec3 intersPoint_Backup = myEnv->intersPoint;
    glm::vec3 intersNorm_Backup = myEnv->intersNorm;
    //double tValueMax_Backup = myEnv->tValueMax;
    double currentLowestT = myEnv->tValueMax;
    double kS_Backup = kS;

    // Now, just as before, our camera position will now become our intersection point
    myEnv->camPosition = myEnv->intersPoint;
    // And our camDirection will now become the reflected camDirection ray
    glm::vec3 reflectedRay = reflect(camDirection_Backup, intersNorm_Backup);
    //myEnv->camDirection = glm::normalize(reflectedRay);

    // ===== Closest intersection calculation =====
    vector<SceneObject>::size_type closestObject = 0; //Stores closest object to camera
    bool containsIntersection = false;
    glm::vec3 closestIntersPt(0, 0, 0);
    glm::vec3 closestIntersNrm(0, 0, 0);
    // ======================================
    for(vector<SceneObject>::size_type itr = 0; itr != oA.size(); itr++){ //Traverse all scene objects
        if(oA[itr]->isIntersected(myEnv, reflectedRay) == true){
            // ===== Closest shadow calculation =====
            containsIntersection = true;
            if(myEnv->tValue < currentLowestT){ //Update new nearest hit
                currentLowestT = myEnv->tValue;
                closestIntersPt = myEnv->intersPoint;
                closestIntersNrm = myEnv->intersNorm;
                closestObject = itr;
            }
            if(myEnv->tValue > currentLowestT){
                myEnv->tValue = currentLowestT;
                myEnv->intersPoint = closestIntersPt;
                myEnv->intersNorm = closestIntersNrm;
            }
            // ======================================
        }
    }

//    cout << "After parsing object array" << endl;
//    cout << "myEnv->camPosition = [" << myEnv->camPosition.x << ", " << myEnv->camPosition.y << ", " << myEnv->camPosition.z << "]" << endl;
//    cout << "myEnv->intersPoint = [" << myEnv->intersPoint.x << ", " << myEnv->intersPoint.y << ", " << myEnv->intersPoint.z << "]" << endl;
//    cout << "reflectedRay = [" << reflectedRay.x << ", " << reflectedRay.y << ", " << reflectedRay.z << "]" << endl;
//    cout << "closestIntersPt = [" << closestIntersPt.x << ", " << closestIntersPt.y << ", " << closestIntersPt.z << "]" << endl;
//    cout << "Distance from cameraPos to closestIntersPt = " << glm::length(closestIntersPt - myEnv->camPosition) << endl;

    if(containsIntersection){ //Reflection
        float reflR = 0;
        float reflG = 0;
        float reflB = 0;
        oA[closestObject]->getColour(reflR, reflG, reflB);
        // Now recursively calculate the next reflection
        myEnv->reflectionDepth = myEnv->reflectionDepth - 1;
        // Get our reflected object's kSpecular component
        double refl_kSpecular;
        oA[closestObject]->getSpecular(refl_kSpecular);
        if(kS != 0)
            computeReflection(myEnv, oA, reflR, reflG, reflB, refl_kSpecular);
        // Blend the two colours together
        myR = ((kS * reflR) + (1 - kS) * myR);
        myG = ((kS * reflG) + (1 - kS) * myG);
        myB = ((kS * reflB) + (1 - kS) * myB);
        // Clamp our final values
        if(myR > 255) myR = 255; if(myR < 0) myR = 0;
        if(myG > 255) myG = 255; if(myG < 0) myG = 0;
        if(myB > 255) myB = 255; if(myB < 0) myB = 0;

//        cout << "\nFound a reflection at t = " << myEnv->tValue << endl;
//        cout << "incident ray = " << camDirection_Backup.x << ", " << camDirection_Backup.y << ", " << camDirection_Backup.z << "]" << endl;
//        cout << "intersPoint = [" << intersPoint_Backup.x << ", " << intersPoint_Backup.y << ", " << intersPoint_Backup.z << "]" << endl;
//        cout << "intersection normal = [" << intersNorm_Backup.x << ", " << intersNorm_Backup.y << ", " << intersNorm_Backup.z << "]" << endl;
//        cout << "reflectedRay = [" << reflectedRay.x << ", " << reflectedRay.y << ", " << reflectedRay.z << "]" << endl;
//        cout << "This object's kSpecular = " << kS << endl;
//        cout << "((kS * (double)reflR) = " << kS * (double)reflR << endl;
//        double temp = 0;
//        oA[closestObject]->getSpecular(temp);
//        cout << "Reflected object's kSpecular = " << temp << endl;
//        cout << "Reflected object's colour (R, G, B) = (" << reflR << ", " << reflG << ", " << reflB << ")" << endl;
//        cout << "Writing in colour (R, G, B) = (" << (int)myR << ", " << (int)myG << ", " << (int)myB << ")\n" << endl;
    } else {
        // Blend into black
//        cout << "Blending into black." << endl;
        myR = ((kS * 0) + (1 - kS) * myR);
        myG = ((kS * 0) + (1 - kS) * myG);
        myB = ((kS * 0) + (1 - kS) * myB);
        // Clamp our final values
        if(myR > 255) myR = 255; if(myR < 0) myR = 0;
        if(myG > 255) myG = 255; if(myG < 0) myG = 0;
        if(myB > 255) myB = 255; if(myB < 0) myB = 0;
    }

    myEnv->camPosition = camPosition_Backup; //Reset values
    myEnv->camDirection = camDirection_Backup;
    myEnv->intersPoint = intersPoint_Backup;
    myEnv->intersNorm = intersNorm_Backup;
//    myEnv->tValueMax = tValueMax_Backup;
//    tValueMax_Backup = myEnv->tValueMax;
    kS = kS_Backup;
}

