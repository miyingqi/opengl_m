#ifndef SHADER_H
#define SHADER_H
/*
shader的暂行版本只能处理一个shade_v.txt和shader_f.txt文件
*/
#include<glad.h>
#include<string>
#include<fstream>
#include<sstream> 
#include<iostream>
class Shader{
    public:
    Shader(const std::string vertexpath,
    const std::string fragmentpath)
    {
        // 
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.open(vertexpath);
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vertexCode = vShaderStream.str();

        fShaderFile.open(fragmentpath);
        std::stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fragmentCode = fShaderStream.str();
    }
    void initVShader(){
    const GLchar* vShaderCode = vertexCode.c_str();
    glShaderSource(Vertex, 1, &vShaderCode, NULL);
    glCompileShader(Vertex);
    int  success;
    char infoLog[512];
    glGetShaderiv(Vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(Vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    }
    void initFShader(){
    const GLchar* fShaderCode = fragmentCode.c_str();
    glShaderSource(Fragment, 1, &fShaderCode, NULL);
    glCompileShader(Fragment);
    int success;
    char infoLog[512];
    glGetShaderiv(Fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(Fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    }
    void CreatProgram(){
        shaderProgram=glCreateProgram();
        glAttachShader(shaderProgram, Vertex);
        glAttachShader(shaderProgram, Fragment);
        glLinkProgram(shaderProgram);

    }
    void CreatShader(){
        Vertex=glCreateShader(GL_VERTEX_SHADER);
        Fragment=glCreateShader(GL_FRAGMENT_SHADER);
        initVShader();
        initFShader();
        CreatProgram();
    }
    void UseShder()
    {
        glUseProgram(shaderProgram);
    }
    void DeleteShader(){
        glDeleteShader(Vertex);
        glDeleteShader(Fragment);
    }
    unsigned int returnShader(){
        return shaderProgram;
    }
    private:
        std::string vertexCode;
        std::string fragmentCode;
        unsigned int Vertex, Fragment;
        unsigned int shaderProgram;
};

#endif