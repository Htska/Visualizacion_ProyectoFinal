#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#include "Function.h"

class Trigonometric:public Function
{
public:
    float f(float x, float z) override;
    
    void print() override;
};

#endif