#include "Trigonometric.h"
#include <iostream>

float Trigonometric::f(float x, float z){
    float y = cos(x)+sin(z);
    return y;
}

void Trigonometric::print(){
    std::cout<< "La función es: f(x,z)= cos(x)+sin(z);\n";
}