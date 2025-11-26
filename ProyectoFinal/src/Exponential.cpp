#include "Exponential.h"
#include <iostream>

float Exponential::f(float x, float z){
    float y = exp(-1*((x*x)+(z*z)));
    return y;
}

void Exponential::print(){
    std::cout<< "La función es: f(x,y) = e^(-(x^2+y^2))\n";
}

std::vector<float> Exponential::grad(float x, float z){
    float value = f(x,z);
    float dx = -2*x*value;
    float dz = -2*z*value;
    std::vector<float> gradient = {};
    gradient.push_back(dx);
    gradient.push_back(dz);
    return gradient;
}