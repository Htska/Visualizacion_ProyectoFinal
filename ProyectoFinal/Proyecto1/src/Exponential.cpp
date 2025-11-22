#include "Exponential.h"
#include <iostream>

float Exponential::f(float x, float z){
    float y = exp(-1*((x*x)+(z*z)));
    return y;
}

void Exponential::print(){
    std::cout<< "La función es: e^(-(x^2+z^2))\n";
}