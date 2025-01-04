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
        char infoLog[512]{0};
        glGetShaderiv(Vertex, GL_COMPILE_STATUS, &success);
        if(!success){
        glGetShaderInfoLog(Vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        memset(infoLog, 0, sizeof(infoLog));
        const GLchar* fShaderCode = fragmentCode.c_str();
        glShaderSource(Fragment, 1, &fShaderCode, NULL);
        glCompileShader(Fragment);
        success=0;
        glGetShaderiv(Fragment, GL_COMPILE_STATUS, &success);
        if(!success){
        glGetShaderInfoLog(Fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //链接着色器
        ID=glCreateProgram();
        glAttachShader(ID, Vertex);
        glAttachShader(ID, Fragment);
        glLinkProgram(ID);
        //删除着色器
        glDeleteShader(Vertex);
        glDeleteShader(Fragment);
    }
    ~Shader(){
        glDeleteProgram(ID);
    }
    //------------------------------------------------------------------------
    void Use()
    {
        glUseProgram(ID);
    }
    //------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    unsigned int returnShader(){
        return ID;
    }
private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }


    // 程序ID
    unsigned int ID;
};

#endif