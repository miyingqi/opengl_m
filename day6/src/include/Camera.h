#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
static float base=-5.0f;
// 定义摄像机移动的几个可能选项 用作抽象，以远离特定于窗口系统的输入方法
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    SHIFT
};

// 默认摄像机值
//偏航角
const float YAW         = -90.0f;
//俯仰角
const float PITCH       =  0.0f;
// 摄像机移动速度
const float SPEED       =  2.5f;
// 摄像机鼠标灵敏度
const float SENSITIVITY =  0.1f;    
// 摄像机缩放
const float ZOOM        =  45.0f;


// 一个抽象的相机类，用于处理输入并计算相应的欧拉角、矢量和矩阵，以便在 OpenGL 中使用
class Camera
{
public:
    // camera 属性
    // 摄像机位置
    glm::vec3 Position;
    // 摄像机方向
    
    glm::vec3 Front;
    //上向量
    glm::vec3 Up;
    //右向量
    glm::vec3 Right;
    
    glm::vec3 WorldUp;
    // 欧拉 角度
    float Yaw;
    float Pitch;
    // 相机选项
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // 带有 vector 的构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // 具有标量值的构造函数
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // 返回使用 Euler Angles 和 LookAt Matrix 计算的视图矩阵
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if( direction == UP)
        Position += Up * velocity;
    //确保用户停留在地面上
     // <这一条衬垫使用户保持在地面（xz 平面）
}
    // 处理从任何键盘（如输入系统）接收的输入以相机定义的 枚举 的形式接受输入参数（从窗口系统中抽象出来）
    void  ProcessKeyboard(Camera_Movement direction, float deltaTime,float yy)
    {
        float lasttime=0.0f;
        float velocity = MovementSpeed * deltaTime;
        float temp=Position.y;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        if( direction == UP&&Position.y==base&&(yy-lasttime)*deltaTime>0.2f)
        {
            Position.y+=0.175f/2.0f * velocity;
            temp=Position.y;
            lasttime=yy;
            std::cout<<"up";
        }
        if( direction == SHIFT)
        {
            Position.y -= velocity;
        }
        Position.y=temp;
        std::cout<<yy-lasttime;
    }

    // 处理从鼠标输入系统接收的输入 期望 x 和 y 方向的偏移值
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // 确保当 Pitch 超出界外时，屏幕不会被翻转
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // 使用更新的欧拉 角更新 Front、Right 和 Up Vectors
        updateCameraVectors();
    }

    // 处理从鼠标滚轮事件接收的输入只需要垂直滚轮轴上的输入
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }
    void physis(float yy,float deltaTime){
            if(Position.y>base){
        Position.y -= (yy* deltaTime);
    }
    }
private:
    // 根据摄像机的 （更新的） 欧拉角 计算前向量
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif