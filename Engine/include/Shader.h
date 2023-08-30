#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "Common.h"

class Shader
{
private:
    std::string mVertexShader;
    std::string mFragmentShader;
    std::string mGeometryShader;

    std::ifstream mVertexShaderFile;
    std::ifstream mFragmentShaderFile;
    std::ifstream mGeometryShaderFile;
    unsigned int mId;

    void checkCompileErrors(unsigned int shader, std::string type);
    void checkUniformErrors(const std::string& name, int flag) const;

public:
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    Shader(std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");
    ~Shader();

    void use() const
    {
        glUseProgram(mId);
    }
    inline unsigned int getProgram()
    {
        return mId;
    }

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};
