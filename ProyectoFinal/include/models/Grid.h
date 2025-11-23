#ifndef GRID_H
#define GRID_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Model.h"
#include "Function.h"
#include "Exponential.h"

class Grid:public Model
{

private:
    
    int m_width = 0;
	int m_depth = 0; // Profundidad de la malla 
    Function* m_f;
    float m_min{};
    float m_max{};
    /**
     * @brief valor por el cual se va a escalar el modelo de la malla
     */
    float m_scale{};

    /**
     * @brief flotante para calcular la escala de la matriz del modelor
     */
    float m_model_scale{};

    struct Vertex
    {
        glm::vec3 Pos; 
        
        /**
         * @brief Inicializa el atributo Pos de cada Vertex 
         */
        void InitVertex(int x, int y, int z);
    };

    void initGeometry() override;
    
    void init() override;
    
    /**
     * @brief Genera una lista de triangulos que componen a cada QUAD de una grid 
     */
    void CreateTriangleList();

    /**
     * @brief Inicializa cada vertice de la Grid en base al width y depth  
     * @param Vertices referencia a una lista de vertices para inicializar 
     */
    void InitVertices(std::vector<Vertex>& Vertices);

    /**
     * @brief Inicializa indices para los veritces de la malla  
     * @param Vertices 
     */
    void InitIndices(std::vector<uint>& Indices);

public: 

    Grid(ShaderProgram* program, int width, int depth, Function* f, float scale,float model_scale) 
        : Model(program)
        , m_width{width}
        , m_depth{depth}
        , m_f{f}
        , m_scale{scale}
        , m_model_scale{model_scale}
    {
        CreateTriangleList();
    }

    void renderModel(const glm::mat4& view, const glm::mat4& projection, GLenum mode) override;

    void updateModel(float deltaTime) override;

    void finish() override;

    void printInfo() override;

    /**
     * Función para regresar la escala usada por el modelo
     */
    float getScale();

    /**
     * Función para regesar la escala del modelo
     */
    float getModelScale();

    /**
     * Función para obtener el ancho
     */
    int getWidth();

    /**
     * Función para obtener la profundiad
     */
    int getDepth();

    /**
     * Función para obtener la función usada
     */
    Function* getFunction();
};


#endif