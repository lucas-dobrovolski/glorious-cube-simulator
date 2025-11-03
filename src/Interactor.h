#pragma once
#include "UI.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Window.h"

class Interactor {
public:
    static void Interactor::handle(GLFWwindow* windowptr, UI& ui, Camera& camera) {

    if (Input::isKeyJustPressed(GLFW_KEY_I, true)) {  // true = ignorar ImGui
        camera.uiMode = !camera.uiMode;
        ui.toggleInfoWindow();

            
        if (camera.uiMode) {
            glfwSetInputMode(windowptr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(windowptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            Input::resetFirstMouse();  // Evitar saltos de cámara
        }
    }

    // Cerrar ventana
    if (Input::isKeyPressed(GLFW_KEY_ESCAPE, true)) {
        glfwSetWindowShouldClose(windowptr, true);
    }

}

private:
    GLFWwindow* window;
};
