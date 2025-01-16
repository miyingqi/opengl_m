#include<glad.h>
//#include<glad.c>
//#include<glew.h>
#include<glfw3.h>
#include<iostream>
#include <string>
#include<vector>
#include<glad.c>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <random>
#include"Shader.h"
#include"Camera.h"
#include"Model.h"
const unsigned int SCR_WIDTH = 1960;
const unsigned int SCR_HEIGHT = 1024;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

GLFWwindow* init();
float DTime = 0.0f;
float lastTime = 0.0f;
Camera camera(glm::vec3(2.0f, 2.0f, -2.0f), SCR_WIDTH, SCR_HEIGHT);

int main()
{
	GLFWwindow* windows = init();


	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	while (!glfwWindowShouldClose(windows))
	{
		processInput(windows);
		float nowTime = glfwGetTime();
		DTime = nowTime - lastTime;
		lastTime = nowTime;

		glClearColor(0.3f, 0.4f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        
		glfwSwapBuffers(windows);
		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.cameraMove(C_FRONT, DTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.cameraMove(C_BACK, DTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.cameraMove(C_LEFT, DTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.cameraMove(C_RIGHT, DTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.cameraMove(C_UP, DTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.cameraMove(C_SHIFT, DTime);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.ProcessMouseMovement(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
GLFWwindow* init() {
	GLFWwindow* windows;
	int success = 0;
	success = glfwInit();
	if (!success) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return 0;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	windows = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, " opengl", NULL, NULL);
	glfwMakeContextCurrent(windows);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glfwSetInputMode(windows, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetCursorPosCallback(windows, mouse_callback);
	glfwSetScrollCallback(windows, scroll_callback);
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);
	return windows;
}
