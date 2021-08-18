#include <iostream>
#include "Platform.h"
#include "BuildType.h"
#include "RAssert.h"
#include "Vector.h"
#include "Matrix.h"

int main(){

    std::cout << "Hello World" << std::endl;

    int a = 10;
    int* b = &a;
    std::cout<<b<<std::endl;
    std::cout<<reinterpret_cast<long long int>(b)<<std::endl;


    std::cin.get();
    return 0;
    
}