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
    float aspect;
    bool uiMode = true; // si true → no controla la cámara
    float farPlane ;
    float nearPlane ;
    float fov;
    Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 3.0f));

    void update();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    void setAspectFromFramebuffer(GLFWwindow*);
private:
    bool cursorChanged = false;
    void updateVectors();
};
