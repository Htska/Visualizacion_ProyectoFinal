#include "Scene.h"

void Scene::init(int selection){
    //Inicializacion de ventana
    Function* f;
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    ShaderProgram* m_shaderProgram2 = new ShaderProgram("shaders/vertex_shader2.glsl","shaders/frag_shader2.glsl");
    ShaderProgram* m_shaderProgram3 = new ShaderProgram("shaders/vertex_shader3.glsl","shaders/frag_shader3.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);
    m_shaderPrograms.push_back(m_shaderProgram2);
    m_shaderPrograms.push_back(m_shaderProgram3);
    //Se inicializan todos los modelos a usar
    m_axes = new Axes(m_shaderPrograms[0]);
     if (selection == 1){
        f = new Trigonometric();
        m_model = new Grid(m_shaderPrograms[1],10,10,f,1.0f,0.22f);//[5,5]
        m_gradient = new Gradient(m_shaderPrograms[2],100,100,f,10.0f,0.022f);
    } else if (selection == 2){
        f = new Exponential();
        m_model = new Grid(m_shaderPrograms[1],10,10,f,5.0f,0.22f);//[2,2]
        m_gradient = new Gradient(m_shaderPrograms[2],100,100,f,50.0f,0.022f);
    } else {
        f = new Cone();
        m_model = new Grid(m_shaderPrograms[1],100,100,f,100.0f,0.022f);//[1,1]
        m_gradient = new Gradient(m_shaderPrograms[2],100,100,f,100.0f,0.022f);
    }
    //m_gradient = new Gradient(m_shaderPrograms[2],50,50,f);
    //Function* g = new Exponential();
    //std::cout << "Cargando función 2\n";
    //Model* model7 = new Grid(m_shaderPrograms[1],100,100,g,50.0f,0.022f);
    //m_models.push_back(model6);
    //m_models.push_back(axes);
    //m_models.push_back(model6);
    //m_models.push_back(model7);
    //Matriz de vista View Matrix
    m_view =  glm::lookAt(glm::vec3(2.0f,1.0f,2.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    m_model->printInfo();
    m_model->setPrinted(true);
    //float axis = 0.0f;
    GLenum mode = GL_TRIANGLES;
    bool scale_up = false;
    bool scale_down = false;
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
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_H) == GLFW_RELEASE){
            m_model->renderModel(m_view, m_projection,mode);
        }
        m_axes->renderModel(m_view, m_projection,GL_LINES);
        m_gradient->renderModel(m_view,m_projection,GL_LINES);
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

          

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S)){
            scale_up = true;
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D)){
            scale_down = true;
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_1) == GLFW_PRESS && scale_up){
            int width = m_model->getWidth()*10;
            int depth = m_model->getDepth()*10;
            float scale = m_model->getScale()*10;
            float modelScale = m_model->getModelScale()/10;
            Function* f = m_model->getFunction();
            m_model = new Grid(m_shaderPrograms[1],width,depth,f,scale,modelScale);
            scale_up = false;
        }

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_0) == GLFW_PRESS && scale_down){
            int width = m_model->getWidth()/10;
            int depth = m_model->getDepth()/10;
            float scale = m_model->getScale()/10;
            float modelScale = m_model->getModelScale()*10;
            Function* f = m_model->getFunction();
            m_model = new Grid(m_shaderPrograms[1],width,depth,f,scale,modelScale);
            scale_down = false;
        }

    }

}