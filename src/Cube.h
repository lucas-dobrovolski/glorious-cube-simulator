#pragma once
#include <glad/glad.h>
#include "ObjX.h"

class Cube : public ObjX {
private:
    unsigned int VAO, VBO;

public:
    Cube();            // Constructor: genera VAO/VBO y sube los datos
    ~Cube();           // Destructor: limpia buffers

    void draw() const; // Dibuja el cubo
};

