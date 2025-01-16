#pragma once
#include"Shader.h"
#include"Model.h"
#include<map>
#include<string>
#include <stb/stb_image.h>
class Resource
{
public:
	static std::map<std::string,Shader> Shaders;
	static std::map<std::string, _2D::Texture2D> Textures;
	static Shader LoadShader(std::string name,const std::string vpath, const std::string fpath, const std::string gpath = "");
	static Shader GetShader(const std::string name);
	static _2D::Texture2D LoadTexture(std::string name, std::string path, bool value = false);
	static _2D::Texture2D GetTexture2D(std::string name);
	static void Clear();
private:
	Resource() {};
	static Shader loadShaderFile( const std::string vpath, const std::string fpath, const std::string gpath = "");
	static _2D::Texture2D loadTextureFile( std::string path, bool value);
};

