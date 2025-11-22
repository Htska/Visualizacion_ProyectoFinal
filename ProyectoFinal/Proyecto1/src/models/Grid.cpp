#include <iostream>
#include <limits>
#include "models/Grid.h"


void Grid::CreateTriangleList(){

    init();
    
    initGeometry();

    finish();

}

void Grid::Vertex::InitVertex(int x, int y, int z){
    Pos=glm::vec3(x,y,z);
}

 void Grid::InitVertices(std::vector<Vertex>& Vertices) {
     int Index{0};

     // Se inician los valores máximos
     m_min = std::numeric_limits<float>::max();
     m_max = std::numeric_limits<float>::min();
     for (int z = -m_depth / 2; z < m_depth /2; z++) {
         for (int x = -m_width /2; x < m_width /2; x++) {
            // Se calculan las coordenadas escalads
            float new_x = x/m_scale;
            float new_z = z/m_scale;
            // El valor de la función
            float y = m_f->f(new_x,new_z);
            // Se escala el valor de y
            if (m_scale >2.0f)
                y = y*(m_scale/2);
            if (y>m_max)
                m_max=y;
            if (y<m_min)
                m_min = y;
            //std::cout << "x: "<<new_x <<" y: "<<y<< " z: "<< new_z<<"\n";
            Vertices[Index].InitVertex(x, y,z);
            Index++;
         }
     }

}



void Grid::InitIndices(std::vector<uint>& Indices){

    int Index{0};

    for(int z=0; z< m_depth-1 ; z++){
        for(int x=0; x< m_width-1; x++){

            uint IndexBottomLeft = z * m_width + x; 
            uint IndexTopLeft = (z+1) * m_width + x; 
            uint IndexTopRight = (z+1) * m_width + (x+1);
            uint IndexBottomRight = z * m_width + (x+1);


            //Add top Left Triangle 
            Indices[Index++]=IndexBottomLeft; 
            Indices[Index++]=IndexTopLeft; 
            Indices[Index++]=IndexTopRight; 

            //Add Bottom Right Triangle
            Indices[Index++]=IndexBottomLeft;
            Indices[Index++]=IndexTopRight;
            Indices[Index++]=IndexBottomRight; 
        }
    }

}



void Grid::initGeometry(){
    std::vector<Grid::Vertex> vertices; 
    vertices.resize(m_width*m_depth);
    
    InitVertices(vertices);
    //Populate the VBO 

    //Init indices 
    std::vector<unsigned int> Indices; 
    int NumQuads = (m_width-1)*(m_depth-1);
    Indices.resize(NumQuads*6);// Cada Quad tiene 6 vertices 
    InitIndices(Indices);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW); 

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0])*Indices.size(), &Indices[0],GL_STATIC_DRAW);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // -> Para modo wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // -> Para modo wireframe

    // La escala se precalcula para calcularla en el update 
    m_model_mat = glm::mat4(1.0f);
    m_model_mat = glm::translate(m_model_mat, glm::vec3(0.0f));
    m_model_mat = glm::scale(m_model_mat, glm::vec3(m_model_scale)); // SOLO una vez
}

void Grid::init(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    //Enable vertex attribute
    // size_t NumFloats = 0; 
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(NumFloats*sizeof(float)));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

}

void Grid::renderModel(const glm::mat4& view, const glm::mat4& projection,GLenum mode){

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);
    m_shaderProgram->setFloat("max",m_max);
    m_shaderProgram->setFloat("min",m_min);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);


    // glDrawArrays(GL_POINTS, 0, m_depth*m_width);
    // glDrawElements(GL_POINTS, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, NULL);
    glDrawElements(mode, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, nullptr);
    // glDrawElements(GL_TRIANGLES, (m_depth-1)*(m_width-1)*6, GL_UNSIGNED_INT, NULL);
    

    glBindVertexArray(0);
}   

void Grid::updateModel(float deltaTime){
    //m_model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f));
    if (deltaTime == 0.0f)
        return;
    else if (deltaTime == 1.0f)
        m_model_mat=glm::rotate(m_model_mat,glm::radians(0.7f), glm::vec3(1.0f, 0.0f, 0.0f));
        else if (deltaTime == 2.0f)
            m_model_mat=glm::rotate(m_model_mat,glm::radians(0.7f), glm::vec3(0.0f, 1.0f, 0.0f));
        else 
            m_model_mat=glm::rotate(m_model_mat,glm::radians(0.7f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Grid::finish(){
    // Des-vincula los Buffers 
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
void Grid::printInfo(){
    if (m_printed)
        return;
    m_f->print();
    std::cout << "Su dominio es: [" << -m_width/(2*m_scale) <<"," << m_width/(2*m_scale) << "] X [" << -m_depth/(2*m_scale) << "," << m_depth/(2*m_scale)<< "]\n";
    float min = m_min;
    float max = m_max;
    // Se regresa a los mínimos originales
    if (m_scale>2.0f){
        min = (2*m_min)/(m_scale);
        max = (2*m_max)/(m_scale);
    }
    std::cout << "El mínimo es: " << min <<"\n";
    std::cout << "El máximo es: " << max <<"\n";
    float new_scale = m_scale<2.0f? m_scale:m_scale/2;
    std::cout << "Las coordenadas x,z están escaladas por: "<< new_scale <<"\n";
    std::cout << "La coordenada y está escalada por: " << new_scale << "\n";
}