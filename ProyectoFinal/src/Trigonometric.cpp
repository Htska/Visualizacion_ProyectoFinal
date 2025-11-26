#include "Trigonometric.h"
#include <iostream>

float Trigonometric::f(float x, float z){
    float y = cos(x)+sin(z);
    return y;
}

void Trigonometric::print(){
    std::cout<< "La función es: f(x,y)= cos(x)+sin(y);\n";
}

std::vector<float> Trigonometric::grad(float x, float z){
    float dx = -1*sin(x);
    float dz = cos(z);
    std::vector<float> gradient = {};
    gradient.push_back(dx);
    gradient.push_back(dz);
    return gradient;
}