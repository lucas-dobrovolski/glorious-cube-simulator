#pragma once
#include <glad/glad.h>

class Cube {
private:
    unsigned int VAO, VBO;

public:
    Cube();            // Constructor: genera VAO/VBO y sube los datos
    ~Cube();           // Destructor: limpia buffers

    void draw() const; // Dibuja el cubo
};

