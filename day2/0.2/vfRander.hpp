#ifndef _vfRander_hpp_
#define _vfRander_hpp_
#include<glad.h>
#include<glad.c>
#include<vector>
#include <functional>
#include<glfw3.h>
#include <glm.hpp>
struct vertex{  
      float x,y,z;
      
    };


class Rander{
    public:
    std::vector<vertex> vertices;
    Rander(){}
    ~Rander(){}
    void initRander(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(float), (void*)(vertices.size()/2*sizeof(float)));
    glEnableVertexAttribArray(1);
    }
    template<class T>
    T firstrander(std::function<T()> func){
        return func();
    }
    unsigned reVAO(){
        return VAO;
    }
    unsigned reVBO(){
        return VBO;
    }
    private:
    

    
    unsigned int VBO, VAO;

};
#endif