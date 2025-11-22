#include "models/ImportedModel.h"

void ImportedModel::initGeometry(){
    // Se lee obj especificado
    ModelImporter modelImporter = ModelImporter();
    modelImporter.parseOBJ(m_filePath);
    //Se obtiene la información del modelo
    numVertices=modelImporter.getNumVertices();
    realVertices = modelImporter.getRealVertices();
    std::vector<float> verts = modelImporter.getVertices();
    std::vector<float> tcs = modelImporter.getTextureCoordinates();
    std::vector<float> normals = modelImporter.getNormals();
    max = modelImporter.getMax();
    min = modelImporter.getMin();
    /*for (float v: max)
        std::cout << v << "\n";
    for (float m : min)
        std::cout << m << "\n";*/
    // Para centrar el modelo, se calcula un cubo que envuelva a todo el modelo y así poder trasladar y escalar adecuadamente
    glm::vec3 centro = glm::vec3((max[0]+min[0])*0.5f,(max[1]+min[1])*0.5f,(max[2]+min[2])*0.5f);
    glm::vec3 dimension = glm::vec3((max[0]-min[0]),(max[1]-min[1]),(max[2]-min[2]));
    float factor = 1.0f/(float)(std::max({dimension.x,dimension.y,dimension.z}));
    //std::cout << factor<< "\n";
    glm::mat4 escalamiento = glm::scale(glm::mat4(1.0f),glm::vec3(factor));
    //glm::mat4 traslacion = glm::translate(glm::mat4(1.0f),-centro);
    // SE calcula la matriz del modelo
    m_model_mat = glm::translate(escalamiento,-centro);

    for(int i=0; i<numVertices;i++){
        
        m_vertices.push_back(verts[i*3]);
        m_vertices.push_back(verts[i*3+1]);
        m_vertices.push_back(verts[i*3+2]);
        
        m_textCoords.push_back(tcs[i*2]);
        m_textCoords.push_back(tcs[i*2+1]);

        m_normalVecs.push_back(normals[i*3]);
        m_normalVecs.push_back(normals[i*3+1]);
        m_normalVecs.push_back(normals[i*3+2]);

    }

}

void ImportedModel::init(){

    glGenVertexArrays(1,&VAO);
    glGenBuffers(3, m_VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    if(m_vertices.size()>0){
        //std::cout<<"Vertices: "<<realVertices<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]); 
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"VERTICES ERROR"<<std::endl; 
    }

    if(m_textCoords.size()>0){
        //std::cout<<"Texture Coordinates: "<<m_textCoords.size()<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(float), &m_textCoords[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"TEXTURE COORDINATES ERROR"<<std::endl; 
    }

    if(m_normalVecs.size()>0){
        //std::cout<<"Normal Vectors: "<<m_normalVecs.size()<<'\n';
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), &m_normalVecs[0], GL_STATIC_DRAW);
    }else{
        std::cerr<<"NORMALS ERROR"<<std::endl; 
    }

}

void ImportedModel::renderModel(const glm::mat4& view, const glm::mat4& projection,GLenum mode){

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);
    // Se le pasa al shader los valoers maximos y mínimos en altura
    m_shaderProgram->setFloat("max",max[1]);
    m_shaderProgram->setFloat("min",min[1]);

    glBindVertexArray(VAO); 
    // Esto tal vez debería ir en init (Profe)
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //glDrawArrays(GL_POINTS, 0, numVertices);
    glDrawArrays(mode, 0, numVertices);
    //glDrawArrays(GL_LINES, 0, numVertices);

}

// Se hace la rotación segun indique la variable deltatime
void ImportedModel::updateModel(float deltaTime){
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

void ImportedModel::finish(){

}

void ImportedModel::printInfo(){
    if (m_printed)
        return;
    std::cout << "Nombre del archivo: " << m_filePath << "\n";
    std::cout << "Número de vértices: " << realVertices << "\n";
    std::cout << "Valores Máximos- x: " << max[0] << " y: " << max[1] << " z: " << max[2] <<"\n";
    std::cout << "Valores Mínimos- x: " << min[0] << " y: " << min[1] << " z: " << min[2] <<"\n";
}