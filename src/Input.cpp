    #include "Input.h"
    #include <imgui.h>  // Para usar ImGui::GetIO si querés integrarlo directamente

    bool Input::keys[1024] = { false };
    bool Input::keysProcessed[1024] = { false };
    bool Input::mouseButtons[8] = { false };
    double Input::mouseX = 0.0;
    double Input::mouseY = 0.0;
    double Input::lastMouseX = 0.0;
    double Input::lastMouseY = 0.0;
    double Input::deltaX = 0.0;
    double Input::deltaY = 0.0;
    bool Input::firstMouse = true;
    ImGuiIO* Input::io = nullptr;
    // ============================================
    // Inicialización
    // ============================================
    void Input::init(GLFWwindow* window) {
        glfwSetKeyCallback(window, keyCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, cursorPosCallback);
    }

    // ============================================
    // Integración opcional con ImGui
    // ============================================
    void Input::setImGuiIO(ImGuiIO* ioPtr) {
        io = ioPtr;
    }

    // ============================================
    // Actualización (llamar 1 vez por frame)
    // ============================================
    void Input::update() {
        deltaX = mouseX - lastMouseX;
        deltaY = mouseY - lastMouseY;
        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    // ============================================
    // Consultas de estado
    // ============================================
    bool Input::isKeyPressed(int key, bool ignoreImGuiCapture) {
        if (!ignoreImGuiCapture && io && io->WantCaptureKeyboard) 
            return false; // ImGui usa teclado
        
        if (key >= 0 && key < 1024)
            return keys[key];
        return false;
    }

    bool Input::isKeyJustPressed(int key, bool ignoreImGuiCapture) {
        bool pressed = isKeyPressed(key, ignoreImGuiCapture);
        
        if (pressed && !keysProcessed[key]) {
            keysProcessed[key] = true;
            return true;
        }
        if (!pressed) {
            keysProcessed[key] = false;
        }
        return false;
    }


    bool Input::isMouseButtonPressed(int button) {
        if (io && io->WantCaptureMouse) return false; // ImGui usa mouse
        if (button >= 0 && button < 8)
            return mouseButtons[button];
        return false;
    }

    double Input::getMouseX() { return mouseX; }
    double Input::getMouseY() { return mouseY; }
    double Input::getMouseDeltaX() { return deltaX; }
    double Input::getMouseDeltaY() { return deltaY; }

    // ============================================
    // Callbacks de GLFW
    // ============================================
    void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key >= 0 && key < 1024) {
            if (action == GLFW_PRESS)
                keys[key] = true;
            else if (action == GLFW_RELEASE)
                keys[key] = false;
        }
    }

    void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (button >= 0 && button < 8) {
            if (action == GLFW_PRESS)
                mouseButtons[button] = true;
            else if (action == GLFW_RELEASE)
                mouseButtons[button] = false;
        }
    }

    void Input::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        mouseX = xpos;
        mouseY = ypos;

        if (firstMouse) {
            lastMouseX = xpos;
            lastMouseY = ypos;
            firstMouse = false;
        }
    }

    // ============================================
    // Nuevo método para resetear firstMouse
    // ============================================
    void Input::resetFirstMouse() {
        firstMouse = true;
    }