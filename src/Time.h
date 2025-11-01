#pragma once
#include <chrono>

class Time {
public:
    static void init();
    static void update();

    static float deltaTime();         // Tiempo entre frames
    static float timeSinceStart();    // Tiempo total desde que arrancó

private:
    static std::chrono::high_resolution_clock::time_point startTime;
    static std::chrono::high_resolution_clock::time_point lastFrameTime;
    static float delta;
};
