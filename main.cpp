#include <iostream>
#include "Platform.h"
#include "BuildType.h"
#include "RAssert.h"
#include "Vector.h"
#include "Matrix.h"


int main(){

    std::cout << "Hello World" << std::endl;

    REngine::Vector3f vec3(1.0f);
    std::cout<<vec3<<std::endl;
    REngine::Matrix4x4f mat4 = REngine::GetIdentityMatrix();
    REngine::Translate(mat4, REngine::Vector3f(1.0f, 0.0f, 0.0f));
    std::cout<<mat4;
    REngine::Vector4f vec4 = mat4 * REngine::Vector4f(vec3, 1.0f);
    std::cout<<vec4<<std::endl;


    std::cin.get();
    return 0;
    
}