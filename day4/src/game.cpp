#include"header.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH =1960;
const unsigned int SCR_HEIGHT = 1024;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// 定时
float deltaTime = 0.0f;	// 当前帧和最后一帧之间的时间
float lastFrame = 0.0f;

int main()
{
    // 初始化glfw
    Glfw glfw;
    glfw.creat_window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");

    GLFWwindow* window =glfw.return_window();
    glfwMakeContextCurrent(window);
    //调用回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 禁用光标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    stbi_set_flip_vertically_on_load(true);
    // glad：加载所有 OpenGL 函数指针
    // ---------------------------------------
    glfw.load_Glad();

    // 深度测试

    glEnable(GL_DEPTH_TEST);
    Shader glass_shader("../data/shader/glass.vs","../data/shader/glass.fs");
    Shader Ascence("../data/shader/shader_v.glsl", "../data/shader/shader_f.glsl");
    
    //scence.Use();
    Shader skyShader("../data/shader/sky.vs","../data/shader/sky.fs");
    unsigned int skyVAO=skyboxload();
    unsigned int skytexture=loadcubemap();
    skyShader.setInt("skybox",0);

   
    Model glassModel("../data/model/GLASS/GLASS_01.obj");
    glass_shader.setInt("skybox",0);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 计算帧间隔时间
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 输入
        // -----
        processInput(window);

        // 绘图
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // 绑定纹理
        // 调用着色程序
        Ascence.Use();
        
        
        //glm::mat4 transform=glm::mat4(1.0f);
        //transform=glm::rotate(transform,glm::radians(45.0f),glm::vec3(0.1f,0.5f,0.1f));
        //Ascence.setMat4("transform",transform);
        
        // 透视投影矩阵
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        Ascence.setMat4("projection", projection);
        
        // 摄像机视角变换
        glm::mat4 view = camera.GetViewMatrix();
        Ascence.setMat4("view", view);
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                    glm::mat4  model = glm::mat4(1.0f);
                    model = glm::translate( model, glm::vec3(2.0f*i, 2.0f, 2.0f*j));
                    Ascence.setMat4("model", model);
                    glassModel.Draw(glass_shader);
            }
        }
        glDepthFunc(GL_LEQUAL);
        skyShader.Use();
        glm::mat4 skyview = glm::mat4(glm::mat3(view));
        skyShader.setMat4("view",skyview);
        skyShader.setMat4("projection",projection);
        
        glBindVertexArray(skyVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,skytexture);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    
        //glfw：交换缓冲区和轮询 IO 事件（按下的键、释放的键、移动的鼠标等）
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw：终止，清除之前分配的所有 GLFW 资源
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

//process all input：查询 GLFW 是否按下相关键，释放此帧并做出相应反应
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw：每当窗口大小发生变化（通过操作系统或用户调整大小）时，此回调函数都会执行
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 确保视区与新的窗口尺寸匹配;请注意，width 和
    // 高度将明显大于 Retina 显示屏上指定的高度
    glViewport(0, 0, width, height);
}


// glfw：每当鼠标移动时，此回调都会被调用
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 反转，因为 Y 坐标从下到上

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw：每当鼠标滚轮滚动时，该回调被调用
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}