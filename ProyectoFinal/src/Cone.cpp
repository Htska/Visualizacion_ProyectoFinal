#include "Cone.h"
#include <iostream>

float Cone::f(float x, float z){
    return sin(10*sqrt(x*x+z*z))/10;
}

void Cone::print(){
    std::cout<< "La función es: sen(10 sqrt(x^2+y^2))/10\n";
}