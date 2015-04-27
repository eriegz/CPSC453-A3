#include "Shading.h"

void Shading::computeShading(Environment* myEnv, vector<SceneObject*> oA, float &myR, float &myG, float &myB){
    //Calculate all shadow rays, store them in a vector
    vector<glm::vec3> sRays;
    for(vector<glm::vec3>::size_type itr = 0; itr != myEnv->lightSources.size(); itr++){
//        cout << "\n==== New shadow ray calculation ======" << endl;
//        cout << "myEnv->lightSources[itr] = ["
//             << myEnv->lightSources[itr].x << ", "
//             << myEnv->lightSources[itr].y << ", "
//             << myEnv->lightSources[itr].z << "]" << endl;
        glm::vec3 shadowRay = glm::normalize(myEnv->lightSources[itr] - myEnv->intersPoint);
        sRays.push_back(shadowRay);
    }

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
                myR *= .995; myG *= .995; myB *= .995; //Darken all the colours a bit, for now
                break; //We can break at the first shadow from this light source
            }
        }
        myEnv->tValue = tCopy; //Reset t, as it gets changed by intersection calculations
    }
    myEnv->camPosition = camPos_copy; //Set our camPosition back to its original value
}

void Shading::calculateShadow(){

}
