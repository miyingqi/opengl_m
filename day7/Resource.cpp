#include "Resource.h"
std::map<std::string, Shader> Resource::Shaders;
std::map<std::string, _2D::Texture2D> Resource::Textures;

Shader Resource::LoadShader(std::string name, const std::string vpath, const std::string fpath, const std::string gpath ) {
	Shaders[name] = loadShaderFile(vpath,fpath,gpath);
	return Shaders[name];
}
Shader Resource::GetShader(const std::string name) {
	return Shaders[name];
}
_2D::Texture2D Resource::LoadTexture(std::string name, std::string path, bool value ) {
	Textures[name] = loadTextureFile(path, value);
	return Textures[name];
}
_2D::Texture2D Resource::GetTexture2D(std::string name) {
	return Textures[name];
}
void Resource::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}
Shader Resource::loadShaderFile(const std::string vpath, const std::string fpath, const std::string gpath ) {
	Shader shader;
	shader.compile(vpath, fpath, gpath);
	return shader;
}
_2D::Texture2D Resource::loadTextureFile(std::string path, bool value){
	_2D::Texture2D texture;
	if (value)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	int width, height;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
	texture.Generate(width, height, image);
	stbi_image_free(image);
	return texture;
}