#include "models/Line.h"

/**
 * @brief Se construye los arreglos para los vértices y para el EBO
 */
void Line::initGeometry(){
    float x = m_x*m_new_scale;
    float z = m_z*m_new_scale;
    vertices[0] = x; vertices[1] = m_f->f(m_x,m_z)*(m_new_scale/2); vertices[2] = z;
    std::vector<float> gradient = m_f->grad(m_x,m_z);
    //std::cout<<"aaaa\n";
    float dx = gradient[0];
    float dz = gradient[1];
    float norm = sqrt(dx*dx+dz*dz);
    dx = dx/norm;
    dz = dz/norm;
    m_gradient_length = norm;
    //vertices[0] = m_x; vertices[1] = m_f->f(m_x,m_z); vertices[2] = m_z;
    vertices[3] = x + 0.3*dx; vertices[4] =  (m_f->f(m_x,m_z)*(m_new_scale/2)+0.03*(dx*dx+dz*dz)); vertices[5] = z+0.3*dz;
    //std::cout << "Los puntos x, y: " << vertices[0]<<","<<vertices[2]<<"\n";
    //std::cout << "El gradiente: " << vertices[3]<<","<<vertices[5]<<"\n";
    indices[0] = 0; indices[1] = 1;
    m_model_mat = glm::mat4(1.0f);
    m_model_mat = glm::translate(m_model_mat, glm::vec3(0.0f));
    m_model_mat = glm::scale(m_model_mat, glm::vec3(m_scale)); 
}

/**
 * @brief se inicia los VBO,VAO y EBO
 */
void Line::init(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

/**
 * @brief Se renderiza el modelo 
 */
void Line::renderModel(const glm::mat4& view, const glm::mat4& projection, GLenum mode){

    m_shaderProgram->use();

    m_shaderProgram->setFloat("grad_length",m_gradient_length);
    m_shaderProgram->setMat4x4("model",m_model_mat);
    m_shaderProgram->setMat4x4("view",view);
    m_shaderProgram->setMat4x4("projection",projection);

    glBindVertexArray(VAO);
    glDrawElements(mode,2,GL_UNSIGNED_INT,0);
}

void Line::updateModel(float deltaTime){
    delta = deltaTime;
}

void Line::finish(){
    
}

void Line::printInfo(){
    std::cout<<"el valor x: "<<m_x<<"\n";
    std::cout<<"el valor z: "<<m_z<<"\n";

}