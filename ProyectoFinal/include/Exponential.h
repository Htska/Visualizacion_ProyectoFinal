#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include "Function.h"

class Exponential:public Function
{
public:
    float f(float x, float z) override;
    
    void print() override;
};

#endif