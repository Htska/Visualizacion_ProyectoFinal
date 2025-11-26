#include <iostream>
#include "models/Gradient.h"





void Gradient::initGeometry(){
    return;
}

void Gradient::init(){
    int depth = m_depth/2;
    int width = m_width/2; 
    //int count = 0;
    for(int z=-depth; z< depth ; z++){
        for(int x=-width; x< width; x++){
            //Le moví aquí
            float new_x = ((float)x)/m_scale;
            float new_z = ((float)z)/m_scale;
            //count++;
            Line* gradient = new Line(m_shaderProgram,new_x,new_z,m_f,m_model_scale);
            m_gradients.push_back(gradient);
        }
    }
    //std::cout<< "cuenta: "<<count<<"\n";
    //std::cout<< "cuenta2: "<<m_gradients.size()<<"\n";

}

void Gradient::renderModel(const glm::mat4& view, const glm::mat4& projection, GLenum mode){
    //std::cout << "numero de gradientes"<<m_gradients.size();
    for (Line* gradient: m_gradients){
        gradient->renderModel(view,projection,mode);
    }
}   

void Gradient::updateModel(float deltaTime){

    m_delta = deltaTime;
}

void Gradient::finish(){
    return; 
}

void Gradient::printInfo(){
    return;
}

