#ifndef SCENE_H 
#define SCENE_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "WindowGL.h"
#include "ShaderProgram.h"

#include "Model.h"
#include "models/Axes.h"
#include "models/Grid.h"
#include "models/Gradient.h"
#include "Function.h"
#include "Exponential.h"
#include "Trigonometric.h"
#include "Cone.h"

/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo 
 */
class Scene
{
private:

    /**
     * La ventana donde se crea la escena
     */
    WindowGL* m_window; 

    /**
     * Vector que contiene los shaders para los diferentes modelos
     */
    std::vector<ShaderProgram*>  m_shaderPrograms;

    /**
     * Vector con los diferentes modelos
     */
    Grid* m_model;

    /**
     * Los ejes coordenados
     */
    Axes* m_axes;

    /**
     * El gradiente de la función
     */
    Gradient* m_gradient;

    /**
     * Matriz de la vista
     */
    glm::mat4 m_view;

    /**
     * Matriz de proyección
     */
    glm::mat4 m_projection; 

    /**
     * @brief Inicializacion 
     */
    void init(int selection);

public:

    Scene(int selection){
        init(selection);
    }

    ~Scene(){
        delete m_window;
        for (ShaderProgram* sh:m_shaderPrograms)
            delete sh;
    }

    /**
     * @brief Ciclo de renderizado general 
     */
    void render(); 

};



#endif