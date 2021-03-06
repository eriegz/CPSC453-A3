#include "Shading.h"

void Shading::computeShading(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB, double kD, double kS){
    // Exemption for panel lights
    if(myR == 255 && myG == 255 && myB == 255)
        return;

    // Calculate all shadow rays, store them in a vector
    vector<glm::vec3> sRays;
    for(vector<glm::vec3>::size_type itr = 0; itr != myEnv->lightSources.size(); itr++){
        glm::vec3 shadowRay = glm::normalize(myEnv->lightSources[itr] - myEnv->intersPoint);
        sRays.push_back(shadowRay);
    }

    // Save a copy of myEnv's tValue, as it's going to be overwritten a bunch
    double tCopy = myEnv->tValueMax;
    double currentLowestT = tCopy; //Save our closest shadow intersection
    // Next, save copies of everything
    glm::vec3 intersPoint_Backup = myEnv->intersPoint;
    glm::vec3 camPos_copy = myEnv->camPosition;
    myEnv->camPosition = myEnv->intersPoint;
    glm::vec3 intersNorm_Backup = myEnv->intersNorm;

    // Now, we traverse all the shadow rays. If a ray reports an intersection
    // with an object, then the original point is in the shadow of that light source.
    for(vector<glm::vec3>::size_type itr_i = 0; itr_i != sRays.size(); itr_i++){ //For all shadow rays
        // ===== Closest shadow calculation =====
        vector<SceneObject>::size_type closestObject = 0; //Stores closest object to camera
        bool containsIntersection = false;
        glm::vec3 closestIntersPt = myEnv->intersPoint;
        // ======================================
        for(vector<SceneObject>::size_type itr_j = 0; itr_j != oA.size(); itr_j++){ //Traverse all scene objects
            if(oA[itr_j]->isIntersected(myEnv, sRays[itr_i]) == true){ //Current object in shadow
                // ===== Closest shadow calculation =====
                float intR, intG, intB;
                oA[itr_j]->getColour(intR, intG, intB);
                if(intR == 255 && intG == 255 && intB == 255)
                    break;
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
            // shadow. Only the ambient component will be added to our Phong shade calculation,
            // and the closer the object, the darker the shadow (attenuation). A tValue of 0.5, for
            // instance, will produce a shadow attenuation factor of:
            //
            //    ( 0.5 / 10 ) * 0.5 + 0.50 = 0.525
            //
            // ...whereas a tValue of 8 will produce an attenuation of:
            //
            //    ( 0.5 / 10 ) * 0.5 + 0.50 = 0.92
            //

            //Use parts of this code later:
            /*
            double shadowAttn = ( myEnv->tValue / (myEnv->tValueMax / 4) ) * 0.5 + 0.50;
            shadowAttn += 0.2;
            if(shadowAttn > 0.95) shadowAttn = 0.95; //Clamp our attenuation factor
            myR *= shadowAttn; myG *= shadowAttn; myB *= shadowAttn; //Darken all the colours a bit, for now
            */

            double kA = myEnv->kAmbient;
            myR *= kA; myG *= kA; myB *= kA; //kA will never be > 1, so no need to clamp RGB values
        } else { //Calculate all 3 Phong components
            // First, pull the colour of our light
            float lightR = myEnv->lightColours[itr_i].x; //Can use itr_i b/c it's just a glm::vec3 type
            float lightG = myEnv->lightColours[itr_i].y;
            float lightB = myEnv->lightColours[itr_i].z;

            // -------- AMBIENT ---------
            // Calculate ambient intensity
            double kA = myEnv->kAmbient;
            double Ia = 1.0; //Will attenuate this later

            double Ii = 1; //Light source intensity to be used for diffuse and specular

            // -------- DIFFUSE ---------
            // Calculate diffuse component
            double dot1 = glm::dot(sRays[itr_i], intersNorm_Backup);
            double Id = Ii * dot1;

            // ------- SPECULAR ---------
            // Calculate specular component
            glm::vec3 negShadowVec = -sRays[itr_i];
            glm::vec3 reflLightRay = glm::normalize(reflect(negShadowVec, intersNorm_Backup));
            glm::vec3 eyeVec = (camPos_copy - intersPoint_Backup);
            glm::vec3 eyeVec_norm = glm::normalize(eyeVec);
            double dot2 = glm::dot(eyeVec_norm, reflLightRay);
            double Is = 0;
            if(dot2 > 0) //Hidden from light source, therefore no specular highlights
                Is = Ii * pow(dot2, 6);

            // Blend our colours
            myR = (kA * Ia * myR) + (kD * Id * myR) + (kS * Is * lightR);
            myG = (kA * Ia * myG) + (kD * Id * myG) + (kS * Is * lightG);
            myB = (kA * Ia * myB) + (kD * Id * myB) + (kS * Is * lightB);

            // Clamp our RGB values (one direction only, b/c our operations are only additive
            if(myR > 255) myR = 255;
            if(myG > 255) myG = 255;
            if(myB > 255) myB = 255;

//            cout << "Writing in colours (R, G, B) = (" << (int)myR << ", " << (int)myG << ", " << (int)myB << ")\n" << endl;
        }
        currentLowestT = tCopy; //Reset current lowest t
        myEnv->tValue = tCopy; //Reset t, as it gets changed by intersection calculations
    }
    myEnv->camPosition = camPos_copy; //Set our camPosition back to its original value
}

void Shading::calculateShadow(){

}
