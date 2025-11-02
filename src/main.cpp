
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

using dot3 = glm::vec3;

const float PI = 3.14159265f;

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
    Cube cube;
    Camera camera(camera_r0); // posición inicial
    
    // ===============  LOOP  ====================

    while(!window1.shouldClose()) { 
                
        window1.clear(rgb0); // R G B 
        
        Time::update();
        float t = Time::timeSinceStart();        

        shader.use();
        
        float x = 1.0f * sin(0.5f * PI * t);
        float y = 1.0f * sin(0.5f * PI * t + PI/2);
        float angle = t * glm::radians(10.0f);
        
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window1.getGLFWwindow(), &fbWidth, &fbHeight);
        float aspect = float(fbWidth) / float(fbHeight);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, angle, glm::vec3(0.5f, x, y));
        model = glm::translate(model, glm::vec3(x, y, -2.0f));  // mover cubo
        camera.update();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
        //                                               fov         ratio   near    far
        
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        
        cube.draw();

        ui.beginFrame();
        ui.show_info(window1);
        ui.render();
        
        Input::update();

        if (Input::isKeyPressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window1.getGLFWwindow(), true);
        }

        if (Input::isKeyJustPressed(GLFW_KEY_I, true)) {  // true = ignorar ImGui
            ui.toggleInfoWindow();
            camera.uiMode = !camera.uiMode;
            
            // Cambiar cursor inmediatamente
            if (camera.uiMode) {
                glfwSetInputMode(window1.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            } else {
                glfwSetInputMode(window1.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                Input::resetFirstMouse();  // Reset para evitar saltos en la cámara
            }
        }
        
        window1.swapBuffers();
        window1.pollEvents();
        
    }
    
    ui.shutdown();

    return 0;
    
}   