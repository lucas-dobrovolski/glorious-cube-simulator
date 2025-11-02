#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
class Window {
private:
GLFWwindow* window;       // puntero a la ventana GLFW
int width, height;        // dimensiones de la ventana
std::string title;        // título de la ventana
bool vsyncEnabled;

public:
// Constructor: inicializa GLFW y crea la ventana
    Window(int w, int h, const std::string& t, bool vsync = true);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    // Destructor: termina GLFW
    ~Window();

    // Devuelve true si la ventana debe cerrarse
    bool shouldClose() const;

    // Intercambia buffers
    void swapBuffers();

    // Procesa eventos (poll)
    void pollEvents();


    // Limpia la pantalla con color de fondo
    void clear(glm::vec3);

    // Getter del puntero GLFWwindow
    GLFWwindow* getGLFWwindow() const { return window; }
    void setVSync(bool enabled);   // <- nuevo método

    bool isVSyncEnabled() const { return vsyncEnabled; }
    
};
