#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <vector>
#include <glm/glm.hpp>

/**
 * Clase auxiliar que se encarga de leer los archivos obj
 */
class ModelImporter{

private: 

    // valores leidos de un OBJ
    std::vector<float> vertVals; 
    std::vector<float> stVals; 
    std::vector<float> normVals; 

    // valores almacenados para ser usados como vertex attributes 
    std::vector<float> triangleVerts; 
    std::vector<float> textureCoords; 
    std::vector<float> normals; 

    // Valores para guardar los máximos y mínimos
    std::vector<float> max;
    std::vector<float> min;
public: 

    ModelImporter();
    void parseOBJ(const char *filePath);
    int getNumVertices(); 
    int getRealVertices();
    std::vector<float> getVertices(); 
    std::vector<float> getTextureCoordinates(); 
    std::vector<float> getNormals();
    std::vector<float> getMax();
    std::vector<float> getMin();
};

#endif