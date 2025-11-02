
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

const float fPI = 3.14159265f;
const long double lPI = 3.141592653589793238462643383279L;

const glm::vec3 camera_r0 = glm::vec3(0.0f, 1.0f, 2.0f);
const glm::vec3 rgb0 = glm::vec3(0.7f, 0.7f, 0.7f);

void world0(){

}

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
    

    // Luego seteas el callback de resize en main
    glfwSetWindowUserPointer(window1.getGLFWwindow(), &camera);
    glfwSetFramebufferSizeCallback(window1.getGLFWwindow(), [](GLFWwindow* w, int width, int height){
        Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
        cam->setAspectFromFramebuffer(w);
        glViewport(0, 0, width, height);
    });
    // ===============  LOOP  ====================
    
    while(!window1.shouldClose()) { 
        
        
        Input::update();
        Interactor::handle(window1.getGLFWwindow(),ui, camera);
        
        Time::update();
        
        window1.clear(rgb0); // R G B 


        // =====================================
        float t = Time::timeSinceStart();        

        shader.use();
        
        float x = 1.0f * sin(0.5f * fPI * t);
        float y = 1.0f * sin(0.5f * fPI * t + fPI/2);
        float angle = t * glm::radians(10.0f);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, angle, glm::vec3(0.5f, x, y));
        model = glm::translate(model, glm::vec3(x, y, -2.0f));  // mover cubo
        camera.update();
        
        shader.setMat4("model", model);
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", camera.getProjectionMatrix());
        
        cube.draw();
        // =====================================

        ui.beginFrame();
        ui.show_info(window1);
        ui.render();

        
        window1.swapBuffers();
        window1.pollEvents();
        
    }
    
    ui.shutdown();

    return 0;
    
}   