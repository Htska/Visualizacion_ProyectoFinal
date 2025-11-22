#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <vector>
#include <glm/glm.hpp>

#include "Model.h"
#include "obj_helpers/ModelImporter.h"


#define num_VBOs 3

/**
 * Clase que define un modelo leído de un archivo obj
 */
class ImportedModel: public Model{
private:

    /**
     * @brief El path del archivo obj
     */
    const char * m_filePath;
    
    /**
     * @brief el número de vértices a pintar
     */
    int numVertices; 

    /**
     * @brief el verdaero número de vértices
     */
    int realVertices;
    // std::vector<glm::vec3> vertices; 
    // std::vector<glm::vec2> texCoords; 
    // std::vector<glm::vec3> normalVecs;

    /**
     * @brief arreglo que contiene los vboos
     */
    GLuint m_VBO[num_VBOs];

    /**
     * Vectores para guardar la información del obj leído
     */
    std::vector<float> m_vertices;
    std::vector<float> m_textCoords;
    std::vector<float> m_normalVecs;
    std::vector<float> max;
    std::vector<float> min;
public: 

    /**
     * Constructor que recibe el shader y la dirección del path a leer
     */
    ImportedModel(ShaderProgram* program, const char *filePath) 
        : Model(program)
        , m_filePath{filePath}
    {

        initGeometry();
        
        init();

    }

    /**
     * Funciones a implementar por heredar de model
     */
    
    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4& view, const glm::mat4& projection,GLenum mode) override;

    void updateModel(float deltaTime) override;

    void finish() override;

    void printInfo() override;
};


#endif