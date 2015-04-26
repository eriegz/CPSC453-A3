#include "Shading.h"

void Shading::computeShading(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB){
    // First, get the vectors to all point light sources, and store them
    // all in a generic vector.
    glm::vec3 shadowRay1 = glm::normalize(myEnv->pointLight1 - myEnv->intersPoint);
    glm::vec3 shadowRay2 = glm::normalize(myEnv->pointLight2 - myEnv->intersPoint);
    glm::vec3 shadowRay3 = glm::normalize(myEnv->pointLight3 - myEnv->intersPoint);
    glm::vec3 shadowRay4 = glm::normalize(myEnv->pointLight4 - myEnv->intersPoint);
    glm::vec3 shadowRay5 = glm::normalize(myEnv->pointLight5 - myEnv->intersPoint);
    glm::vec3 shadowRay6 = glm::normalize(myEnv->pointLight6 - myEnv->intersPoint);
    glm::vec3 shadowRay7 = glm::normalize(myEnv->pointLight7 - myEnv->intersPoint);
    glm::vec3 shadowRay8 = glm::normalize(myEnv->pointLight8 - myEnv->intersPoint);
    glm::vec3 shadowRay9 = glm::normalize(myEnv->pointLight9 - myEnv->intersPoint);
    glm::vec3 shadowRay10 = glm::normalize(myEnv->pointLight10 - myEnv->intersPoint);
    glm::vec3 shadowRay11 = glm::normalize(myEnv->pointLight11 - myEnv->intersPoint);
    glm::vec3 shadowRay12 = glm::normalize(myEnv->pointLight12 - myEnv->intersPoint);

    vector<glm::vec3> sRays;
    sRays.push_back(shadowRay1);
    sRays.push_back(shadowRay2);
    sRays.push_back(shadowRay3);
    sRays.push_back(shadowRay4);
    sRays.push_back(shadowRay5);
    sRays.push_back(shadowRay6);
    sRays.push_back(shadowRay7);
    sRays.push_back(shadowRay8);
    sRays.push_back(shadowRay9);
    sRays.push_back(shadowRay10);
    sRays.push_back(shadowRay11);
    sRays.push_back(shadowRay12);

//    cout << "\n\n <<<<<<<<<<  CALCULATING SHADING >>>>>>>>>>>>\n" << endl;
//    cout << "shadowRay1 = [" << shadowRay1.x << ", " << shadowRay1.y << ", " << shadowRay1.z << "]" << endl;
//    cout << "shadowRay2 = [" << shadowRay2.x << ", " << shadowRay2.y << ", " << shadowRay2.z << "]" << endl;
//    cout << "shadowRay3 = [" << shadowRay3.x << ", " << shadowRay3.y << ", " << shadowRay3.z << "]" << endl;
//    cout << "myEnv->pointLight1 = [" << myEnv->pointLight1.x << ", " << myEnv->pointLight1.y << ", " << myEnv->pointLight1.z << "]" << endl;
//    cout << "myEnv->pointLight2 = [" << myEnv->pointLight2.x << ", " << myEnv->pointLight2.y << ", " << myEnv->pointLight2.z << "]" << endl;
//    cout << "myEnv->pointLight3 = [" << myEnv->pointLight3.x << ", " << myEnv->pointLight3.y << ", " << myEnv->pointLight3.z << "]" << endl;
//    cout << "myEnv->intersPoint = [" << myEnv->intersPoint.x << ", " << myEnv->intersPoint.y << ", " << myEnv->intersPoint.z << "]\n" << endl;

    // Save a copy of myEnv's tValue, as it's going to be overwritten a bunch
    double tCopy = 40;
    // Next, save a copy of camPosition and intersPoint, as camPosition will be replaced with the intersection
    // point in all of the intersection calculations inside this function.
    glm::vec3 camPos_copy = myEnv->camPosition;
    myEnv->camPosition = myEnv->intersPoint;

    // Now, we traverse all the shadow rays. If a ray reports an intersection
    // with an object, then the original point is in the shadow of that light source.
    for(vector<glm::vec3>::size_type itr_i = 0; itr_i != sRays.size(); itr_i++){ //For all shadow rays
        for(vector<SceneObject>::size_type itr_j = 0; itr_j != oA.size(); itr_j++){ //Traverse all scene objects
            if(oA[itr_j]->isIntersected(myEnv, sRays[itr_i]) == true){ //Current object in shadow
//                cout << "\n---------------------------------------------------------->Shadow detected" << endl;
                myR *= .94; myG *= .94; myB *= .94; //Darken all the colours a bit, for now
                break; //We can break at the first shadow from this light source
            }
        }
        myEnv->tValue = tCopy; //Reset t, as it gets changed by intersection calculations
    }
    myEnv->camPosition = camPos_copy; //Set our camPosition back to its original value
}

void Shading::calculateShadow(){

}
