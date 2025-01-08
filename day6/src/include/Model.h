#ifndef _MODEL_H_
#define _MODEL_H_
#include <glad.h>                 //所有头文件 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>        //assimp库头文件
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
//从文件中读取纹理
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
//Model类
class Model
{
public:
	/*  Model数据 */
	//存储到目前为止加载的所有纹理，优化以确保纹理不会被加载多次。
	vector<Texture> textures_loaded{0};
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	/*  函数  */
	// 构造汉化,需要一个3D模型的文件路径
	Model(string const &path);
	~Model(){};
	// 绘制模型，从而绘制所有网格
	void Draw(Shader shader);

private:
	/*  函数   */
	// 从文件加载支持ASSIMP扩展的模型，并将生成的网格存储在网格矢量中。
	void loadModel(string const &path);
	// 以递归方式处理节点。 处理位于节点处的每个单独网格，并在其子节点（如果有）上重复此过程。
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	// 检查给定类型的所有材质纹理，如果尚未加载纹理，则加载纹理。
	// 所需信息作为Texture结构返回。
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif
