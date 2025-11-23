#include "Scene.h"


/**
 * Función principal, se corre la escena
 */
int main(){
    std::cout << "Seleccione el número de la función a visualizar: \n";
    std::cout << "1.- f(x,y)= cos(x)+sin(y)\n";
    std::cout << "2.- f(x,y) = e^(-(x^2+y^2))\n";
    std::cout << "3.- sen(10 sqrt(x^2+y^2))/10\n";
    int selection;
    std::cin >> selection;
    Scene scene {selection};

    scene.render();

    return 0; 
}