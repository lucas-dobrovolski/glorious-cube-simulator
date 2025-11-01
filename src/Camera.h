#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float phi;
    float theta;
    float speed;
    float sensitivity;

    bool uiMode = true; // si true → no controla la cámara

    Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 3.0f));

    void update();
    glm::mat4 getViewMatrix() const;

private:
    bool cursorChanged = false;
    void updateVectors();
};
