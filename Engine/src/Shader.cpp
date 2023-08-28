#include "Shader.h"

std::string DefaultFragmentShader = "";
std::string DefaultVertexShader = "";

Shader::Shader()
{
    Shader(DefaultVertexShader, DefaultVertexShader);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    // mVertexShaderFile =  vertexPath;
    mVertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    mFragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    mGeometryShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        mVertexShaderFile.open(vertexPath);
        mFragmentShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << mVertexShaderFile.rdbuf();
        fShaderStream << mFragmentShaderFile.rdbuf();
        mVertexShaderFile.close();
        mFragmentShaderFile.close();

        mVertexShader = vShaderStream.str();
        mFragmentShader = fShaderStream.str();

        if (geometryPath != nullptr)
        {
            mGeometryShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << mGeometryShaderFile.rdbuf();
            mGeometryShaderFile.close();
            mGeometryShader = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = mVertexShader.c_str();
    const char* fShaderCode = mFragmentShader.c_str();

    unsigned int vertex(0), fragment(0), geometry(0);

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    mId = glCreateProgram();
    glAttachShader(mId, vertex);
    glAttachShader(mId, fragment);

    if (geometryPath)
    {
        const char* gShaderCode = mGeometryShader.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");

        glAttachShader(mId, geometry);
    }

    glLinkProgram(mId);
    checkCompileErrors(mId, "PROGRAM");

    unsigned int uniformBlockIndex = glGetUniformBlockIndex(mId, "CameraMatrices");
    if (uniformBlockIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(mId, uniformBlockIndex, 0);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
}

Shader::Shader(std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
    const char* vShaderCode = mVertexShader.c_str();
    const char* fShaderCode = mFragmentShader.c_str();

    unsigned int vertex(0), fragment(0), geometry(0);

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    mId = glCreateProgram();
    glAttachShader(mId, vertex);
    glAttachShader(mId, fragment);

    if (!geometryShader.empty())
    {
        const char* gShaderCode = mGeometryShader.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, nullptr);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");

        glAttachShader(mId, geometry);
    }

    glLinkProgram(mId);
    checkCompileErrors(mId, "PROGRAM");

    unsigned int uniformBlockIndex = glGetUniformBlockIndex(mId, "CameraMatrices");
    if (uniformBlockIndex != GL_INVALID_INDEX)
    {
        glUniformBlockBinding(mId, uniformBlockIndex, 0);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
}

Shader::~Shader()
{
    glDeleteProgram(mId);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
                "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
                "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::checkUniformErrors(const std::string& name, int flag) const
{
    if (flag == -1)
    {
        std::cout << "FROMENT ERROR: CANT FIND UNIFORM VARIABLE " << name << std::endl;
    }
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), static_cast<int>(value));
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}

// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}

// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniform3f(glGetUniformLocation(mId, name.c_str()), value.x, value.y, value.z);
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    use();
    int flag = glGetUniformLocation(mId, name.c_str());
    if (flag != -1)
    {
        glUniform3f(glGetUniformLocation(mId, name.c_str()), x, y, z);
    }
    else
    {
        checkUniformErrors(name, flag);
    }
}
