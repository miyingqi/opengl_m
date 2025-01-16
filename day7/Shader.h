#pragma once
#include<glad.h>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<glm.hpp>
class Shader {
public:
	unsigned int ID;
	Shader(){}
	void compile(const std::string vspath, std::string fspath,std::string gspath="");
	~Shader() {};
	void Use()const;
	void checkCompileErrors(GLuint object, std::string type);
	void setUniform1i(const std::string& name, int value=0,bool use=false) const;
	void setBool(const std::string& name, bool value, bool use) const;
	void setInt(const std::string& name, int value, bool use = false) const;
	void setFloat(const std::string& name, float value, bool use = false) const;
	void setVec2(const std::string& name, const glm::vec2& value, bool use = false) const;
	void setVec2(const std::string& name, float x, float y ,bool use = false) const;
	void setVec3(const std::string& name, const glm::vec3& value, bool use = false) const;
	void setVec3(const std::string& name, float x, float y, float z, bool use = false) const;
	void setVec4(const std::string& name, const glm::vec4& value, bool use = false) const;
	void setVec4(const std::string& name, float x, float y, float z, float w, bool use = false) const;
	void setMat2(const std::string& name, const glm::mat2& mat, bool use = false) const;
	void setMat3(const std::string& name, const glm::mat3& mat, bool use = false) const;
	void setMat4(const std::string& name, const glm::mat4& mat, bool use = false) const;
};
