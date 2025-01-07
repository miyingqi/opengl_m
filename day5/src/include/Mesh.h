#ifndef _MESH_H_
#define _MESH_H_

#include <glad.h> // 所有头文件
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
	// 位置
	glm::vec3 Position;
	// 法向量
	glm::vec3 Normal;
	// 纹理坐标
	glm::vec2 TexCoords;
	// u向量
	glm::vec3 Tangent;
	// v向量
	glm::vec3 Bitangent;
};
//纹理
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};
class Mesh {
    public:
	//Mesh数据
	//顶点数据
	std::vector<Vertex> vertices;
	//索引数据
	std::vector<unsigned int> indices;
	//纹理数据
	std::vector<Texture> textures;
	//缓冲
	unsigned int VAO;
	//构造函数
	Mesh(){}
	Mesh(std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}
	void Draw(Shader& shader)
	{
		// 绑定适当的纹理
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // 绑定前激活适当的纹理单元
											  // 获取纹理编号（diffuse_textureN中的N）
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);
			// 现在将采样器设置为正确的纹理单元
			glUniform1i(glGetUniformLocation(shader.returnShader(), (name + number).c_str()), i);
			// 最后绑定纹理
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		shader.Use();
		// 画网格
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// 一旦配置完毕将一切设置回默认值总是很好的做法，。
		glActiveTexture(GL_TEXTURE0);
	}

	private:
	unsigned int VBO,EBO;
	void setupMesh(){
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO); //绑定VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //绑定VBO
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW); //将顶点数据存入缓冲
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //绑定EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW); //将索引数据存入缓冲
		//顶点位置
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//顶点法向量
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//顶点纹理坐标
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		//顶点Tangent向量
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//顶点Bitangent向量
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
		glBindVertexArray(0); //解绑VAO
	}
};
#endif