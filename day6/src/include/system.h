#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include<vector>
#include<glad.h>
#include<string>
#include<stb_image.h>
#include<iostream>
#include <array>
#include<glm.hpp>
#include"Shader.h"
#include"Model.h"
struct box_pos{
    float x,y;
};
unsigned int skyboxload();
unsigned int loadcubemap();

class box{
public:
    box_pos apos[2];
    float height;
    box(box_pos a,box_pos b,float h);
    ~box();

};
#endif