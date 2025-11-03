// ObjX.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ObjX {
public:
    glm::vec3 position;
    glm::vec3 rotationEuler;  // Euler angles en radianes
    glm::vec3 rotation; 
    glm::vec3 scale;

    ObjX()
        : position(0.0f), rotationEuler(0.0f), rotation(0.0f), scale(1.0f) {}

    virtual ~ObjX() = default;

    glm::mat4 getModelMatrixEuler() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotationEuler.x, glm::vec3(0,1,0));
        model = glm::rotate(model, rotationEuler.y, glm::vec3(0,0,1));
        model = glm::rotate(model, rotationEuler.z, glm::vec3(0,1,0));
        model = glm::scale(model, scale);
        return model;
    }
    glm::mat4 getModelMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
        model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
        model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
        model = glm::scale(model, scale);
        return model;
    }
};
