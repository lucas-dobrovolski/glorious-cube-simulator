    #include "Window.h"
    #include <GLFW/glfw3.h>
    #include <iostream>

    // Constructor: inicializa GLFW y crea la ventana
    Window::Window(int w, int h, const std::string& t, bool vsync) 
        : width(w), height(h), title(t), vsyncEnabled(vsync)
    {
        if (!glfwInit()) {
            // Inicializar GLFW
            std::cerr << "Error inicializando GLFW\n";
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            std::cerr << "No se pudo crear la ventana\n";
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int newWidth, int newHeight) {
            // Callback de redimensionamiento
            glViewport(0, 0, newWidth, newHeight);
        });

        setVSync(vsyncEnabled);

        glEnable(GL_DEPTH_TEST);
        
    }

    Window::~Window() {
        
        glfwTerminate();
    }

    bool Window::shouldClose() const {
        
        return glfwWindowShouldClose(window);
    }

    void Window::swapBuffers() {
        
        glfwSwapBuffers(window);
    }

    void Window::pollEvents() {
        
        glfwPollEvents();
    }

    void Window::clear(float r, float g, float b) {
        // Limpia la pantalla con color de fondo
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::setVSync(bool enabled){
        vsyncEnabled = enabled;         // Guardás el estado actual
        glfwSwapInterval(enabled ? 1 : 0); // 1 = vsync activado, 0 = desactivado        
    }  