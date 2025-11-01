#include "Time.h"

std::chrono::high_resolution_clock::time_point Time::startTime;
std::chrono::high_resolution_clock::time_point Time::lastFrameTime;
float Time::delta = 0.0f;

void Time::init() {
    startTime = std::chrono::high_resolution_clock::now();
    lastFrameTime = startTime;
}

void Time::update() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> frameDuration = now - lastFrameTime;
    delta = frameDuration.count();  // segundos transcurridos
    lastFrameTime = now;
}

float Time::deltaTime() {
    return delta;
}

float Time::timeSinceStart() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - startTime;
    return elapsed.count();
}
