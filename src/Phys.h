#pragma once
#include "Time.h"
#include "ObjX.h"
#include <cmath>
#include <glm/glm.hpp>

class Phys
{

public:
    // Ejemplo de una transformación simple: movimiento oscilatorio
    static void oscillate(ObjX& obj, glm::vec3 amplitude, glm::vec3 freq, glm::vec3 phase) {
        float t = Time::timeSinceStart();
        obj.position.x = amplitude.x * std::sin(freq.x * t + phase.x);
        obj.position.y = amplitude.y * std::cos(freq.y * t + phase.y);
        obj.position.z = amplitude.z * std::cos(freq.z * t + phase.z);
    }

    static void spin(ObjX& obj, glm::vec3 axis, float angularSpeed) {
       obj.rotation += axis * angularSpeed * Time::deltaTime();
    }

    static void mrua(ObjX& obj, glm::vec3 velocity, glm::vec3 acceleration) {
        float dt = Time::deltaTime();
        velocity += acceleration * dt;
        obj.position += velocity * dt;
    }
};