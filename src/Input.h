#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <imgui.h>

class Input {
public:
    static bool keys[1024];
    static bool keysProcessed[1024];
    static bool mouseButtons[8];
    static double mouseX, mouseY;
    static double lastMouseX, lastMouseY;
    static double deltaX, deltaY;
    static bool firstMouse;
    static ImGuiIO* io;

    // ========== MÉTODOS PÚBLICOS ==========
    static void init(GLFWwindow* window);
    static void setImGuiIO(ImGuiIO* ioPtr);
    static void update();
    
    // Nuevo método para resetear firstMouse
    static void resetFirstMouse();  // ← AÑADE ESTA LÍNEA

    // Métodos de consulta
    static bool isKeyPressed(int key, bool ignoreImGuiCapture = false);
    static bool isKeyJustPressed(int key, bool ignoreImGuiCapture = false);
    static bool isMouseButtonPressed(int button);
    static double getMouseX();
    static double getMouseY();
    static double getMouseDeltaX();
    static double getMouseDeltaY();

private:
    // Callbacks
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif