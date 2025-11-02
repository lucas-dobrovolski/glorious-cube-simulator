#pragma once
#include "UI.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Window.h"

class Interactor {
public:
    static void handle(GLFWwindow*, UI&, Camera&);

private:
    GLFWwindow* window;
};
