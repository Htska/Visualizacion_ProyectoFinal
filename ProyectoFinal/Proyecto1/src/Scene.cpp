#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    ShaderProgram* m_shaderProgram2 = new ShaderProgram("shaders/vertex_shader2.glsl","shaders/frag_shader2.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);
    m_shaderPrograms.push_back(m_shaderProgram2);
    //Se inicializan todos los modelos a usar
    Model* axes = new Axes(m_shaderPrograms[0]);
    std::cout << "Cargando Modelo 1\n";
    Model* model1 = new ImportedModel(m_shaderPrograms[1],"assets/obj/bunny.obj");
    std::cout << "Cargando Modelo 2\n";
    Model* model2 = new ImportedModel(m_shaderPrograms[1],"assets/obj/Cube_Triangles.obj");
    std::cout << "Cargando Modelo 3\n";
    Model* model3 = new ImportedModel(m_shaderPrograms[1],"assets/obj/dragon.obj");
    std::cout << "Cargando Modelo 4\n";
    Model* model4 = new ImportedModel(m_shaderPrograms[1],"assets/obj/Happy_Buddha.obj");
    std::cout << "Cargando Modelo 5\n";
    Model* model5 = new ImportedModel(m_shaderPrograms[1],"assets/obj/Teapot.obj");
    std::cout << "Cargando función 1\n";
    Function* f = new Trigonometric();
    Model* model6 = new Grid(m_shaderPrograms[1],1000,1000,f,100.0f,0.0022f);
    Function* g = new Exponential();
    std::cout << "Cargando función 2\n";
    Model* model7 = new Grid(m_shaderPrograms[1],1000,1000,g,500.0f,0.0022f);
    m_models.push_back(model1);
    m_models.push_back(model2);
    m_models.push_back(model3);
    m_models.push_back(model4);
    m_models.push_back(model5);
    m_models.push_back(axes);
    m_models.push_back(model6);
    m_models.push_back(model7);
    //Matriz de vista View Matrix
    m_view =  glm::lookAt(glm::vec3(2.0f,1.0f,2.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    Model* m_model = m_models[0];
    m_model->printInfo();
    float axis = 0.0f;
    GLenum mode = GL_TRIANGLES;
    //Ciclo de Renderizado
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario
    glm::vec3 cameraPos = glm::vec3(2.0f,1.0f,2.0f);

    while(!glfwWindowShouldClose(m_window->getWindow())){
        // Compute time  
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        // Segun la tecla, se visualiza un modelo u otro y se restablecen sus valores para imprimir
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_0) == GLFW_PRESS){
            m_model = m_models[0];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[1]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[6]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_1) == GLFW_PRESS){
            m_model = m_models[1];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[6]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_2) == GLFW_PRESS){
            m_model = m_models[2];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[1]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[6]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_3) == GLFW_PRESS){
            m_model = m_models[3];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[1]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[6]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_4) == GLFW_PRESS){
            m_model = m_models[4];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[1]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[6]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_F) == GLFW_PRESS){
            m_model = m_models[6];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[1]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[7]->setPrinted(false);
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_G) == GLFW_PRESS){
            m_model = m_models[7];
            m_model->printInfo();
            m_model->setPrinted(true);
            m_models[0]->setPrinted(false);
            m_models[1]->setPrinted(false);
            m_models[2]->setPrinted(false);
            m_models[3]->setPrinted(false);
            m_models[4]->setPrinted(false);
            m_models[6]->setPrinted(false);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Segpun las teclas, se visualiza como puntos, linea o triangulos
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_T) == GLFW_PRESS){
            mode = GL_TRIANGLES;
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_P) == GLFW_PRESS){
            mode = GL_POINTS;
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_L) == GLFW_PRESS){
            mode = GL_LINES;
        }

        // se dibujan los modelos
        m_model->renderModel(m_view, m_projection,mode);
        m_models[5]->renderModel(m_view, m_projection,GL_LINES);
        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        // Segun la tecla se realiza el movimiento de camara
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS){
            cameraPos = cameraPos + glm::vec3(0.05f,0.0f,0.0f);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS){
            cameraPos = cameraPos + glm::vec3(-0.05f,0.0f,0.0f);
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS){
            cameraPos = cameraPos + glm::vec3(0.0f,0.0f,0.05f);
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS){
            cameraPos = cameraPos + glm::vec3(0.0f,0.0f,-0.05f);
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_R) == GLFW_PRESS){
            cameraPos = glm::vec3(2.0f,1.0f,2.0f);
        }

        m_view =  glm::lookAt(cameraPos, glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));

        // Rotaciones segun los ejes
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_X) == GLFW_PRESS){
            axis = 1.0f;
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Y) == GLFW_PRESS){
            axis = 2.0f;
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Z) == GLFW_PRESS){
            axis = 3.0f;
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_N) == GLFW_PRESS){
            axis = 0.0f;
        }
        m_model->updateModel(axis);  
    }

}