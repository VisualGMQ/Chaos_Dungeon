#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

enum class ShaderType{
    VERTEX_SHADER,
    FRAG_SHADER
};

class Program{
public:
    static Program& GetInstance();
    GLuint CompileShader(string filename, ShaderType type);
    bool LinkProgram(GLuint vertex, GLuint frag);
    bool UniformMat4(string name, glm::mat4 mat);
    bool UniformMat3(string name, glm::mat3 mat);
    bool UniformInt(string name, int value);
    bool UniformFloat(string name, float value);
    bool Valid() const;
    void Use();
private:
    static Program program;
    Program();
    Program(string vertex_filename, string frag_filename);
    GLuint prog;
};

#endif
