#ifndef _MOUSE_KEY_H_
#define _MOUSE_KEY_H_
#include"Model.h"
#include"Camera.h"
#include"Shader.h"
#define ZHONGLI 0.1F
class PLAYER{
    public:
    Model*p;
    Camera* p_c;
    PLAYER(std::string path);
    ~PLAYER(){};
    void Draw(Shader shader,int wid,int heig);
};
#endif