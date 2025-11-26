#include "Cone.h"
#include <iostream>

float Cone::f(float x, float z){
    return sin(10*sqrt(x*x+z*z))/10;
}

void Cone::print(){
    std::cout<< "La función es: sen(10*sqrt(x^2+y^2))/10\n";
}

std::vector<float> Cone::grad(float x, float z){
    float dx = (x*cos(10*sqrt(x*x+z*z)))/(sqrt(x*x+z*z));
    float dz = (z*cos(10*sqrt(x*x+z*z)))/(sqrt(x*x+z*z));
    std::vector<float> gradient = {};
    gradient.push_back(dx);
    gradient.push_back(dz);
    return gradient;
}