#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint program;
    
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    
    void use();
    void setMat4(const std::string& name, const float* value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setFloat(const std::string& name, float value);
    void setInt(const std::string& name, int value);
    
private:
    GLuint compileShader(const char* source, GLenum type);
    std::string loadShaderSource(const char* path);
};
