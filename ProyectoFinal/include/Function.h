#ifndef FUNCTION_H
#define FUNCTION_H
#include <vector>
/**
 * @class Function
 * @brief Clase para ser derivada de diversas funciones
 */
class Function{

public:
    /**
     * @brief Funcion a aplicar
     * @param x valor en x
     * @param z valor en z
     * @returns el valor evaluado
     */
    virtual float f(float x, float z) = 0;

    /**
     * @brief Función para imprimir f(x)
     */
    virtual void print() = 0;

    /**
     * @brief Función que regresa el vector gradiente
     */
    virtual std::vector<float> grad(float x, float z) = 0;
};


#endif