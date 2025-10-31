#pragma once
#include "Window.h"
#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class UI {
private:
    bool showInfoWindow = true; // empieza visible

public:
    UI(Window& window);               // Constructor: inicializa ImGui
    void beginFrame();                 // Inicia un frame de ImGui
    void toggleInfoWindow();  // método para cambiar su estado
    void show_info(Window& window);                 // Dibuja la ventanita “Hola”
    void render();                     // Renderiza la UI
    void shutdown();                   // Cierra ImGui correctamente
    void show_FPS();
};
