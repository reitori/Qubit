#include <QubitPCH.h>
#include "Qubit/Platform/Renderer/Utility/Shader.h"

unsigned int Shader::GetProgram() {
	return programID;
}

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
	std::ifstream vertexFS(vertexFilePath);
	std::ifstream fragmentFS(fragmentFilePath);

	std::string vertStr;
	std::string fragStr;

	vertexFS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFS.exceptions(std::fstream::failbit | std::ifstream::badbit);

	try {

		vertexFS.seekg(0, std::ios::end);
		fragmentFS.seekg(0, std::ios::end);
		vertStr.reserve(fragmentFS.tellg());
		fragStr.reserve(fragmentFS.tellg());
		vertexFS.seekg(0, std::ios::beg);
		fragmentFS.seekg(0, std::ios::beg);

		vertStr.assign((std::istreambuf_iterator<char>(vertexFS)), std::istreambuf_iterator<char>());
		fragStr.assign((std::istreambuf_iterator<char>(fragmentFS)), std::istreambuf_iterator<char>());
	}

	catch (std::ifstream::failure e) {
		Qubit::Log::printError("Shader file not successfully read!", Qubit::Log::getCoreLogger());
	}

	const char* vertexShader = vertStr.c_str();
	const char* fragmentShader = fragStr.c_str();

	char infoLog[512];
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glCompileShader(vertex);

	int successful;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &successful);
	if (!successful) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::string str = "OPENGL::SHADER:VERTEX\n";
		str += infoLog + '\n';
		Qubit::Log::printError(str.c_str(), Qubit::Log::getCoreLogger());
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &successful);
	if (!successful) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::string str = "OPENGL::SHADER::FRAGMENT\n";
		str += infoLog + '\n';
		Qubit::Log::printError(str.c_str(), Qubit::Log::getCoreLogger());
	}

	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex);
	glAttachShader(this->programID, fragment);
	glLinkProgram(this->programID);

	glGetProgramiv(this->programID, GL_LINK_STATUS, &successful);
	if (!successful) {
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::string str = "OPENGL::PROGRAM::LINKING_FAILED\n";
		str += infoLog + '\n';
		Qubit::Log::printError(str.c_str(), Qubit::Log::getCoreLogger());
	}


	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

uint32_t Shader::GetUniformLocation(const std::string& name) const {
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations.at(name);

	uint32_t location = glGetUniformLocation(programID, name.c_str());
	m_UniformLocations.insert({ name, location });
	return location;
}

void Shader::SetBool(std::string& name, bool value) const
{
    glUniform1i(GetUniformLocation(name), (int)value);
}
// ------------------------------------------------------------------------
void Shader::SetInt(std::string& name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}
// ------------------------------------------------------------------------
void Shader::SetFloat(std::string& name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}
// ------------------------------------------------------------------------
void Shader::SetVec2(std::string& name, const glm::vec2& value) const
{
    glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}
void Shader::SetVec2(std::string& name, float x, float y) const
{
    glUniform2f(GetUniformLocation(name), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(std::string& name, const glm::vec3& value) const
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}
void Shader::SetVec3(std::string& name, float x, float y, float z) const
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(std::string& name, const glm::vec4& value) const
{
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}
void Shader::SetVec4(std::string& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}


void Shader::UseProgram() {
	glUseProgram(programID);
}
