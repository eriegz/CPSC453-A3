#include "Shading.h"

void Shading::computeShading(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB){
    //Calculate all shadow rays, store them in a vector
    vector<glm::vec3> sRays;
    for(vector<glm::vec3>::size_type itr = 0; itr != myEnv->lightSources.size(); itr++){
        glm::vec3 shadowRay = glm::normalize(myEnv->lightSources[itr] - myEnv->intersPoint);
        sRays.push_back(shadowRay);
    }

    // Save a copy of myEnv's tValue, as it's going to be overwritten a bunch
    double tCopy = myEnv->tValueMax;
    double currentLowestT = tCopy; //Save our closest shadow intersection
    // Next, save a copy of camPosition and intersPoint, as camPosition will be replaced with the intersection
    // point for all of the intersection calculations inside this function.
    glm::vec3 camPos_copy = myEnv->camPosition;
    myEnv->camPosition = myEnv->intersPoint;

    // Now, we traverse all the shadow rays. If a ray reports an intersection
    // with an object, then the original point is in the shadow of that light source.
    double phongShading = 0;
    for(vector<glm::vec3>::size_type itr_i = 0; itr_i != sRays.size(); itr_i++){ //For all shadow rays
        // ===== Closest shadow calculation =====
        vector<SceneObject>::size_type closestObject = 0; //Stores closest object to camera
        bool containsIntersection = false;
        glm::vec3 closestIntersPt = myEnv->intersPoint;
        // ======================================
        for(vector<SceneObject>::size_type itr_j = 0; itr_j != oA.size(); itr_j++){ //Traverse all scene objects
            if(oA[itr_j]->isIntersected(myEnv, sRays[itr_i]) == true){ //Current object in shadow
                // ===== Closest shadow calculation =====
                containsIntersection = true;
                if(myEnv->tValue < currentLowestT){
                    currentLowestT = myEnv->tValue;
                    closestIntersPt = myEnv->intersPoint;
                    closestObject = itr_j;
                }
                if(myEnv->tValue > currentLowestT){
                    myEnv->tValue = currentLowestT;
                    myEnv->intersPoint = closestIntersPt;
                }
                // ======================================
            }
        }
        if(containsIntersection){ //Point is in shadow
            // Inside here, the point is in shadow, and we know that it is the closest object's
            // shadow. Only the diffuse component will be added to our Phong shade calculation,
            // and the closer the object, the darker the shadow (attenuation). A tValue of 0.5, for
            // instance, will produce a shadow attenuation factor of:
            //
            //    ( 0.5 / 10 ) * 0.5 + 0.50 = 0.525
            //
            // ...whereas a tValue of 8 will produce an attenuation of:
            //
            //    ( 0.5 / 10 ) * 0.5 + 0.50 = 0.92
            //
            double shadowAttn = ( myEnv->tValue / (myEnv->tValueMax / 4) ) * 0.5 + 0.55;
            if(shadowAttn > 0.95) shadowAttn = 0.95; //Clamp our attenuation factor
            myR *= shadowAttn; myG *= shadowAttn; myB *= shadowAttn; //Darken all the colours a bit, for now
        }
        currentLowestT = tCopy; //Reset current lowest t
        myEnv->tValue = tCopy; //Reset t, as it gets changed by intersection calculations
    }
    myEnv->camPosition = camPos_copy; //Set our camPosition back to its original value
}

void Shading::calculateShadow(){

}
