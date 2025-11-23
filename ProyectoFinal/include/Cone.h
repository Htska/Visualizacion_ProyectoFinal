#ifndef CONE_H
#define CONE_H

#include "Function.h"

class Cone:public Function
{
public:
    float f(float x, float z) override;
    
    void print() override;
};

#endif