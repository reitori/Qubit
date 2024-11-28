#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>


class Shader {
public:
	//Shader(const char* vertexFilePath, const char* fragmentFilePath);
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexShader, const char* fragmentShader, bool classifier);

    unsigned int GetProgram();
    void UseProgram();
    uint32_t GetUniformLocation(const std::string& name) const;

    void SetBool(std::string& name, bool value) const;
    void SetInt(std::string& name, int value) const;
    void SetFloat(std::string& name, float value) const;
    void SetVec2(std::string& name, const glm::vec2& value) const;
    void SetVec2(std::string& name, float x, float y) const;
    void SetVec3(std::string& name, const glm::vec3& value) const;
    void SetVec3(std::string& name, float x, float y, float z) const;
    void SetVec4(std::string& name, const glm::vec4& value) const;
    void SetVec4(std::string& name, float x, float y, float z, float w);
    void SetMat2(std::string& name, const glm::mat2& mat) const;
    void SetMat3(std::string& name, const glm::mat3& mat) const;
    void SetMat4(std::string& name, const glm::mat4& mat) const;
    void SetLight(std::string& name);
    void SetMVP(std::string& name);

    mutable std::unordered_map<std::string, uint32_t> m_UniformLocations;
private:
	unsigned int programID;
};