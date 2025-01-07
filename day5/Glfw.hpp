#ifndef _GLfw_HPP_
#define _GLfw_HPP_
#include<glad.h>
#include<glfw3.h>
#include<iostream>
enum Mod{
    glfw_core,
    glfw_any
};
class Glfw{
    public:
    Glfw(unsigned int versionBase=3,
    unsigned int versionMinor=3,
    Mod mod=glfw_any){
        int success=1;
        success=glfwInit();
        if(!success){
            std::cout<<"Failed to initialize GLFW"<<std::endl;
            return;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,versionBase);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,versionMinor);
        switch(mod)
        {
        case glfw_core:
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        break;
        case glfw_any:
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
        break;
        }
    }
    void creat_window(
    unsigned int width, unsigned int height,
    const char* title,
    GLFWmonitor* monitor=nullptr,
    GLFWwindow* share=nullptr){
    windows=glfwCreateWindow(width,height,title,monitor,share);
    glfwMakeContextCurrent(windows);
    }

    //加载全部函数指针
    void load_Glad(){
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    }
    auto return_window(){
        return windows;
    }
    ~Glfw() {
        if (windows) {
            glfwDestroyWindow(windows);
        }
        glfwTerminate();
    }
    private:
    GLFWwindow *windows;
};
#endif