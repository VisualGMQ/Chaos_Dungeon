#include "Program.hpp"

Program Program::program;

Program& Program::GetInstance(){
    if(!program.Valid()){
        GLuint vshader = program.CompileShader("shader/shader.vs", ShaderType::VERTEX_SHADER),
                fshader = program.CompileShader("shader/shader.fs", ShaderType::FRAG_SHADER);
        program.LinkProgram(vshader, fshader);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
    }
    return program;
}

Program::Program():prog(0){}

Program::Program(string vertex_filename, string frag_filename){
    GLuint vert = CompileShader(vertex_filename, ShaderType::VERTEX_SHADER),
           frag = CompileShader(frag_filename, ShaderType::FRAG_SHADER);
    LinkProgram(vert, frag);
}

bool Program::Valid() const{
    return prog!=0;
}

GLuint Program::CompileShader(string filename, ShaderType type){
    ifstream file(filename);
    if(file.fail()){
        cerr<<filename<<" not exists"<<endl;
        return 0;
    }
    string str_context((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char* context = str_context.c_str();
    file.close();
    GLuint shader = 0;
    if(type==ShaderType::FRAG_SHADER){
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }else if(type==ShaderType::VERTEX_SHADER){
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    if(shader==0){
        cerr<<"shader create failed"<<endl;
        return 0;
    }
    glShaderSource(shader, 1, &context, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status){
        char buffer[1024] = {0};
        glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer);
        if(type==ShaderType::FRAG_SHADER)
            cerr<<"Fragment shader compile error:"<<endl
                <<buffer<<endl;
        else if(type==ShaderType::VERTEX_SHADER)
            cerr<<"Vertex shader compile error:"<<endl
                <<buffer<<endl;
    }
    return shader;
}

bool Program::LinkProgram(GLuint vertex, GLuint frag){
    prog = glCreateProgram();
    glAttachShader(prog, vertex);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    GLint result;
    glGetProgramiv(prog, GL_LINK_STATUS, &result);
    if(!result){
        char buffer[1024];
        glGetProgramInfoLog(prog, sizeof(buffer), nullptr, buffer);
        cerr<<"program link error:"<<endl
            <<buffer<<endl;
        return false;
    }
    return true;
}

bool Program::UniformMat4(string name, glm::mat4 mat){
    GLint loc = glGetUniformLocation(prog, name.c_str());
    if(loc==-1){
        cerr<<name<<" uniform not fount"<<endl;
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    return true;
}

bool Program::UniformMat3(string name, glm::mat3 mat){
    GLint loc = glGetUniformLocation(prog, name.c_str());
    if(loc==-1){
        cerr<<name<<" uniform not fount"<<endl;
        return false;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    return true;
}

bool Program::UniformInt(string name, int value){
    GLint loc = glGetUniformLocation(prog, name.c_str());
    if(loc==-1){
        cerr<<name<<" uniform not fount"<<endl;
        return false;
    }
    glUniform1i(loc, value);
    return true;
}

bool Program::UniformFloat(string name, float value){
    GLint loc = glGetUniformLocation(prog, name.c_str());
    if(loc==-1){
        cerr<<name<<" uniform not fount"<<endl;
        return false;
    }
    glUniform1f(loc, value);
    return true;
}

void Program::Use(){
    glUseProgram(prog);
}
