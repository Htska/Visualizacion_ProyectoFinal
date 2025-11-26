#ifndef LINE_H
#define LINE_H
#include "Model.h"
#include "Function.h"
#include <vector>

class Line:public Model 
{
private:

    float m_x{};
    float m_z{};

    Function* m_f;
    
    GLfloat vertices[6];
    GLuint indices[2];

    float delta;

    float m_scale{};

    float m_gradient_length{};

    float m_new_scale{};

public:

    Line(ShaderProgram* program,float x,float z,Function* f,float scale,float new_scale): 
    Model(program)
    ,m_x{x}
    ,m_z{z}
    ,m_f{f}
    ,m_scale{scale}
    ,m_new_scale{new_scale}
    {
        initGeometry();
        init();
    }

    /**
     * FUnción que inicia la geometría de los ejes
     */
    void initGeometry() override;

    /**
     * Función que inicializa el VAO,VBO,EBO
     */
    void init() override;

    /**
     * Método que renderiza el modelo
     */
    void renderModel(const glm::mat4& view, const glm::mat4& projection, GLenum mode) override;

    /**
     * Método que se encarga de actualizar el modelo
     */
    void updateModel(float deltaTime) override;

    /**
     * Método de finalización.
     */
    void finish() override;

    /**
     * Método para imprimir la información del modélo
     */
    void printInfo() override;
};


#endif