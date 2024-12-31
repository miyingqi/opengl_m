
#include<glad.h>
#include<glfw3.h>
#include<iostream>
#include<glad.c>
int main(int argc, char** argv){
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    } 
    auto windows=glfwCreateWindow(800,600,"First OpenGL",nullptr,nullptr);
    if(!windows){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(windows);
    if(!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    while(!glfwWindowShouldClose(windows))
    {
        glEnable(GL_POINT_SMOOTH);//开启抗锯齿
        glPointSize(128.0f);//设置点的大小
        glBegin(GL_TRIANGLES);//开始画点
        glColor3f(1.0f,0.0f,0.0f);//设置颜色
        glVertex3f(0.0f,0.0f,0.0f);//画点
        glColor3f(1.0f,0.0f,1.0f);//设置颜色
        glVertex3f(-0.5f,0.0f,0.0f);//画点
        glColor3f(1.0f,1.0f,0.0f);//设置颜色
        glVertex3f(0.0f,0.5f,0.0f);//画点
        glEnd();//结束画点
        glfwSwapBuffers(windows);//双缓冲画图
        glfwPollEvents();//获取消息队列
    }

    return 0;

}