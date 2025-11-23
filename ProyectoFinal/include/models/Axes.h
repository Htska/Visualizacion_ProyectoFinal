#ifndef AXES_H
#define AXES_H

#include "Model.h"

/**
 * Clase para modelar los ejes
 */
class Axes: public Model
{
/**
 * Los vértices y el buffer de caras
 */
private:
    GLfloat vertices[24];
    GLuint indices[6];

    float delta;
public:

    /**
     * Constructor de la clase
     * REcibe el shader Program 
     */
    Axes(ShaderProgram* program) : Model(program){
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