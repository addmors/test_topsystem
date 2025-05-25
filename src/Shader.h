#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath, const std::filesystem::path& geometryPath = std::filesystem::path());
    ~Shader();
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setDouble(const std::string &name, double value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setMat4(const std::string& name, const glm::dmat4& mat) const;
private:
    void checkCompileErrors(GLuint shader, std::string type);
};