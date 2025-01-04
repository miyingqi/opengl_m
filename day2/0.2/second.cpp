
#include<glad.h>
#include<glfw3.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>
#include<glad.c>
#include<time.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include"Shader.h"
#include"Glfw.hpp"
#include"vfRander.hpp"


void processInput(GLFWwindow *window);

int main(int argc, char** argv){
    MyGlfw glfw(3,3,glfw_core);
    glfw.creat_window(1024,1024,"myopengl_glfwclass");
    glfw.load_Glad();
    glViewport(0, 0, 1024, 1024);
    Shader shader("../test/shader_v.txt","../test/shader_f.txt");
    
    Rander op;
    op.firstrander<void>([&op](){

    op.vertices = {
        {0.5f, -0.5f, 0.0f},  {1.0f, 0.0f, 0.0f},  // bottom right
        {-0.5f, -0.5f, 0.0f},  {0.0f, 1.0f, 0.0f},  // bottom left
        { 0.0f,  0.5f, 0.0f},  {0.0f, 0.0f, 1.0f }
};

    });
    op.initRander();
    

    

    while (!glfwWindowShouldClose(glfw.return_window()))
    {

    processInput(glfw.return_window());
    // 渲染
    // 清除颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 记得激活着色器
    shader.UseShder();

    // 绘制三角形
    glPointSize(10.0f); // 设置点的大小为10像素
    glEnable(GL_POINT_SMOOTH);//开启抗锯齿

    glBindVertexArray(op.reVAO());
    glDrawArrays(GL_TRIANGLES, 0,3);
    glfwSwapBuffers(glfw.return_window());
    glfwPollEvents();
    }
    shader.~Shader();
    glfw.~MyGlfw();
    return 0;

}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/*
 float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader.returnShader(), "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader.returnShader(), "ourColor");
    glUseProgram(shader.returnShader());
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(float), (void*)(vertices.size()/2*sizeof(float)));
    glEnableVertexAttribArray(1);

*/
    // constexpr int n=100;
    // constexpr float pi=3.1415926f;
    // float radius=0.5f;
    // for(int i=0;i<n;i++){
    //     float angle=2*pi*i/(float)n;
    //     float angle_next=2*pi*(i+1)/(float)n;
    //     vertex v1,v2,v3;
    //     v1={0.0f,0.0f,0.0f};
    //     v2={radius*cos(angle),radius*sin(angle),0.0f};
    //     v3={radius*cos(angle_next),radius*sin(angle_next),0.0f};
    //     op.vertices.push_back(v1);
    //     op.vertices.push_back(v2);
    //     op.vertices.push_back(v3);
    // }
    // op.vertices.push_back({-0.5f,0.5f,0.0f});
    // op.vertices.push_back({-0.5f,-0.5f,0.0f});
    // op.vertices.push_back({0.5f,-0.5f,0.0f});
    // op.vertices.push_back({0.5f,0.5f,0.0f});
    // op.vertices.push_back({-0.5f,0.5f,0.0f});
    // op.vertices.push_back({0.5f,-0.5f,0.0f});
