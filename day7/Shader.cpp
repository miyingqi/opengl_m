#include"Shader.h"

void Shader::compile(const std::string vspath, std::string fspath,std::string gspath) {
	std::string vscode, fscode,gscode;
	std::ifstream vsFile, fsFile,gsFile;
	unsigned int Vertex, Fragment,geometry=0;
	vsFile.open(vspath, std::ios_base::in);
	fsFile.open(fspath, std::ios_base::in);
	vscode = std::string(std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>());
	fscode = std::string(std::istreambuf_iterator<char>(fsFile), std::istreambuf_iterator<char>());
	vsFile.close();
	fsFile.close();
	Vertex = glCreateShader(GL_VERTEX_SHADER);
	Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* code = vscode.c_str();
	glShaderSource(Vertex, 1, &code, NULL);
	glCompileShader(Vertex);
	checkCompileErrors(Vertex, "VERTEX");
	if (gspath != "")
    {
		gsFile.open(gspath, std::ios_base::in);
		gscode= std::string(std::istreambuf_iterator<char>(gsFile), std::istreambuf_iterator<char>());
        code=gscode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &code, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }
	code = fscode.c_str();
	glShaderSource(Fragment, 1, &code, NULL);
	glCompileShader(Fragment);
	checkCompileErrors(Fragment, "VERTEX");
	ID = glCreateProgram();
	glAttachShader(ID, Vertex);
	if(gspath != "")
		glAttachShader(ID, geometry);
	glAttachShader(ID, Fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(Vertex);
	glDeleteShader(Fragment);
	if(gspath!="")
		glDeleteShader(geometry);
}
void Shader::Use()const {
	glUseProgram(ID);
}
void Shader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
//------------------------------------------------------------------------
void Shader::setUniform1i(const std::string& name, int value, bool use) const
{
	if (use)this->Use();
	glUniformBlockBinding(ID,glGetUniformBlockIndex(ID, name.c_str()), value);
}
//------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value, bool use) const
{
	if (use)this->Use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value, bool use) const
{
	if (use)this->Use();
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value, bool use) const
{
	if (use)this->Use();
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value, bool use) const
{
	if (use)this->Use();
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y, bool use) const
{
	if (use)this->Use();
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value, bool use) const
{
	if (use)this->Use();
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z, bool use) const
{
	if (use)this->Use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const glm::vec4& value, bool use) const
{
	if (use)this->Use();
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w, bool use) const
{
	if (use)this->Use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string& name, const glm::mat2& mat, bool use) const
{
	if (use)this->Use();
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string& name, const glm::mat3& mat, bool use) const
{
	if (use)this->Use();
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat, bool use) const
{
	if (use)this->Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}