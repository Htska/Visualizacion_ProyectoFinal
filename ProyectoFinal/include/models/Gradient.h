#ifndef GRADIENT_H
#define GRADIENT_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Model.h"
#include "models/Line.h"
#include "Function.h"

class Gradient:public Model
{

private:
    
    int m_width = 0;
	int m_depth = 0; // Profundidad de la malla 
    Function* m_f{};
    std::vector<Line*> m_gradients;
    float m_scale{};
    float m_model_scale{};
    float m_delta{};

    void initGeometry() override;
    
    void init() override;
    



public: 

    Gradient(ShaderProgram* program, int width, int depth,Function* f,float scale,float model_scale) 
        : Model(program)
        , m_width{width}
        , m_depth{depth}
        , m_f{f}
        , m_scale{scale}
        , m_model_scale{model_scale}
    {
        //std::cout << "tamañoo: "<< m_depth*m_width<<"\n";
        init();
    }

    void renderModel(const glm::mat4& view, const glm::mat4& projection,GLenum mode) override;

    void updateModel(float deltaTime) override;

    void finish() override;

    void printInfo() override;


};


#endif