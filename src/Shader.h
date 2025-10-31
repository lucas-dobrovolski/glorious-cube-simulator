#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {

    private:

        unsigned int ID;

        void checkCompileErrors(unsigned int shader, const std::string& type) const;
    
    public:

        Shader(const char* vertexPath, const char* fragmentPath);

        ~Shader();

        void use() const; // activar shader


        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;

};