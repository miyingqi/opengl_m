#ifndef _TERRAIN_H
#define _TERRAIN_H


#include<glm.hpp>
#include<vector>
#include <iostream>
#include <cmath>
#include<gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define M_PI 3.141592652
#define block_weight 1.6f
#define block_height 6.0f
#define block_width 1.6f

struct Block{
    int ID;
    glm::mat4 model;
};
struct geo_pos{
    float x;
    float y;
    float z;
};
std::vector<geo_pos> generateDensityFunction(int n);
std::vector<Block> generateTerrain(int n);


#endif