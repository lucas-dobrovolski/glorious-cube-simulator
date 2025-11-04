
#include <iostream>

#include <glad/glad.h>  // primero

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Window.h"
#include "Shader.h"
#include "Cube.h"
#include "UI.h"
#include "Input.h"
#include "Camera.h"
#include "Time.h"
#include "Interactor.h"
#include "ObjX.h"
#include "World.h"
#include "Phys.h"

const float fPI = 3.14159265f;
const long double lPI = 3.141592653589793238462643383279L;

const glm::vec3 camera_r0 = glm::vec3(0.0f, 1.0f, 2.0f);
const glm::vec3 rgb0 = glm::vec3(0.7f, 0.7f, 0.7f);

int main() {
    
    // =====  glfw  =====
    Window window1(800, 600, "gcs");
    
    // =====  glad  =====    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // =====  clases  =====  
    Input::init(window1.getGLFWwindow());
    UI ui(window1); // Inicializar ImGui
    ImGuiIO& io = ImGui::GetIO();
    Input::setImGuiIO(&io);
    Shader shader("shaders/vertex.glsl","shaders/fragment.glsl");
    
    // =====  Tiempo  =====
    
    Time::init();
    Camera camera(camera_r0); // posición inicial
    Cube cube;
    World w;

    // =====  Callback para redimensionalizar  =====
    glfwSetWindowUserPointer(window1.getGLFWwindow(), &camera);
    glfwSetFramebufferSizeCallback(window1.getGLFWwindow(), [](GLFWwindow* w, int width, int height){
        Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
        cam->setAspectFromFramebuffer(w);
        glViewport(0, 0, width, height);
    });
    
    // =====  Vector de cubos  =====
    Cube* cube1 = new Cube();
    cube1->position = glm::vec3(1.0f, 3.0f, 0.0f);
    cube1->rotation = glm::vec3(0.0f, glm::radians(45.0f), 0.0f);
    cube1->scale = glm::vec3(1.0f);
    w.cubes.push_back(cube1);

    Cube* cube2 = new Cube();
    cube2->position = glm::vec3(-1.0f, 0.0f, -2.0f);
    cube2->rotation = glm::vec3(0.0f, glm::radians(45.0f), 0.0f);
    cube2->scale = glm::vec3(1.0f);
    w.cubes.push_back(cube2);
    
    // ===============  LOOP  ====================
    
    while(!window1.shouldClose()) { 
        
        // =====  Handle input  =====
        Input::update();
        Interactor::handle(window1.getGLFWwindow(),ui, camera);
        
        // =====  Tiempo  =====
        Time::update();
        window1.clear(rgb0); // R G B   

        shader.use(); // =====  Set shader  =====

        // =====  Protocolo  =====
        Phys::oscillate(*cube1, glm::vec3(1.0,0.7,0.2), glm::vec3(1.0,3.0,1.0) , glm::vec3(0.0, glm::radians(10.0f), 0.0) );          // se mueve en círculo

        // =====  Render  =====
        camera.update();
        w.drawVectorCubes(w.cubes , shader, camera);

        // =====  UI  =====
        ui.beginFrame();
        ui.show_info(window1);
        ui.render();

        // =====  Window  =====
        window1.swapBuffers();
        window1.pollEvents();
        
    }
    
    ui.shutdown();

    return 0;
    
}   