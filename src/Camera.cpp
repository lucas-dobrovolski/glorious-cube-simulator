#include "Camera.h"
#include <iostream>
#include "Time.h"

Camera::Camera(glm::vec3 startPos)
    : position(startPos),
      front(glm::vec3(0.0f,0.0f,-1.0f)),
      up(glm::vec3(0.0f,1.0f,0.0f)),
      right(glm::vec3(1.0f,0.0f,0.0f)),
      worldUp(glm::vec3(0.0f,1.0f,0.0f)),
      phi(-90.0f),
      theta(0.0f),
      speed(5.0f),
      sensitivity(0.1f),
      aspect(1.0f),
      farPlane(500.0f),
      nearPlane(0.001f),
      fov(80.0f)
{
    updateVectors();
}

void Camera::update() {

    // --- Si está en modo UI, no mover cámara ---
    if (uiMode) return;

    
    // --- Movimiento con WASD ---
    float velocity = speed * Time::deltaTime();
    if (Input::isKeyPressed(GLFW_KEY_W, true))
        position += front * velocity;
    if (Input::isKeyPressed(GLFW_KEY_S, true))
        position -= front * velocity;
    if (Input::isKeyPressed(GLFW_KEY_A, true))
        position -= right * velocity;
    if (Input::isKeyPressed(GLFW_KEY_D, true))
        position += right * velocity;

    // --- Rotación con el mouse ---
    float dx = Input::getMouseDeltaX() * sensitivity;
    float dy = Input::getMouseDeltaY() * sensitivity;

    phi += dx;
    theta -= dy;

    if (theta > 89.0f) theta = 89.0f;
    if (theta < -89.0f) theta = -89.0f;

    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 dir;
    dir.x = cos(glm::radians(phi)) * cos(glm::radians(theta));
    dir.y = sin(glm::radians(theta));
    dir.z = sin(glm::radians(phi)) * cos(glm::radians(theta));

    front = glm::normalize(dir);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}   

glm::mat4  Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::setAspectFromFramebuffer(GLFWwindow* window) {
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    aspect = static_cast<float>(fbWidth) / static_cast<float>(fbHeight);
}


