#include "UI.h"

UI::UI(Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::toggleInfoWindow() {
    showInfoWindow = !showInfoWindow; // invierte true/false
}

void UI::show_info(Window& window) {
    if (!showInfoWindow) return;
    
    ImGui::Begin("Info");

    static float deltaTime = 0.0f;
    deltaTime = 0.1f * deltaTime + 0.9f * ImGui::GetIO().DeltaTime;
    float fps = 1.0f / deltaTime;
    ImGui::Text("FPS: %.1f", fps);

    bool vsync = window.isVSyncEnabled();
    if (ImGui::Checkbox("V-Sync", &vsync))
        window.setVSync(vsync);

    // Información adicional útil
    ImGui::Separator();
    ImGui::Text("Controles:");
    ImGui::BulletText("WASD: Movimiento");
    ImGui::BulletText("Mouse: Mirar alrededor");

    ImGui::End();
}

void UI::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::show_FPS() {

    static float deltaTime = 0.0f;
    deltaTime = 0.1f * deltaTime + 0.9f * ImGui::GetIO().DeltaTime;
    float fps = 1.0f / deltaTime;

    ImGui::SetNextWindowPos(ImVec2(10, 10));  // esquina superior izquierda
    ImGui::SetNextWindowBgAlpha(0.35f);       // transparencia

    ImGuiWindowFlags flags = 
        ImGuiWindowFlags_NoDecoration | 
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav;

    ImGui::Begin("FPS Overlay", nullptr, flags);
    ImGui::Text("FPS: %.1f", fps);
    ImGui::End();
}