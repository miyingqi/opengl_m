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
        //所需变量
        std::string vertexCode;
        std::string fragmentCode;
        unsigned int Vertex, Fragment;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //导入并打开着色器
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
        //编译着色器
        Vertex=glCreateShader(GL_VERTEX_SHADER);
        Fragment=glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* vShaderCode = vertexCode.c_str();
        glShaderSource(Vertex, 1, &vShaderCode, NULL);
        glCompileShader(Vertex);
        int  success=0;
        char infoLog[512];
        glGetShaderiv(Vertex, GL_COMPILE_STATUS, &success);
        if(!success){
        glGetShaderInfoLog(Vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        const GLchar* fShaderCode = fragmentCode.c_str();
        glShaderSource(Fragment, 1, &fShaderCode, NULL);
        glCompileShader(Fragment);
        int success0=0;
        char infoLog0[512];
        glGetShaderiv(Fragment, GL_COMPILE_STATUS, &success0);
        if(!success0){
        glGetShaderInfoLog(Fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog0 << std::endl;
        }
        //链接着色器
        shaderProgram=glCreateProgram();
        glAttachShader(shaderProgram, Vertex);
        glAttachShader(shaderProgram, Fragment);
        glLinkProgram(shaderProgram);
        //删除着色器
        glDeleteShader(Vertex);
        glDeleteShader(Fragment);
    }
    ~Shader(){
        glDeleteProgram(shaderProgram);
    }

    void UseShder()
    {
        glUseProgram(shaderProgram);
    }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
    }
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
    }
    unsigned int returnShader(){
        return shaderProgram;
    }
    private:
        // 程序ID
        unsigned int shaderProgram;
};

#endif