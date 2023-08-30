#pragma once
#include "Common.h"
#include "Shader.h"
#include "Camera.h"


enum class VertexLayout
{
    Vertexlayout = 0,
    VertexNormallayout,
    VertexTexcoordlayout,
    VertexNormalTexcoordlayout,
    D2VertexTexcoordlayout
};

enum DrawLayout
{
    None = 0,
    TextureDrawlayout = BIT(0),
    CamerPositionInside = BIT(2),
    NeedSkyBoxTexture = BIT(3),
    InstanceDrawlayout = BIT(4)
};

class Render
{
public:
    Render()
    {
    }

    ~Render();
    virtual void Draw();
    virtual void UpdateCamera();
    Render* SetShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    Render* SetModel(glm::mat4 model);

    // 设置贴图
    Render* SetTextureId(const char* texturePath, const char* uniformName = nullptr);
    Render* SetDrawlayout(unsigned int dl);
    Render* SetDrawTypes(unsigned int dt);
    Shader* GetShader();

    Render* SetVertex(void* v, VertexLayout vertexlayout, int vsize);

    Render* SetVertexFromData(std::string dataPath, unsigned int iv = 0);

    Render* SetVertexNum(int _vn);
    Render* SetVertexLayout(VertexLayout _vt);

protected:
    Shader* shader = nullptr;
    DrawLayout drawlayout = (None);
    unsigned int drawTypes = GL_TRIANGLES;
    // 自身只读数据
    VertexLayout vt = VertexLayout::Vertexlayout;
    unsigned int vn;
    unsigned int instanceNum = 0;
    unsigned int SkyboxTextureID;
    unsigned int VAO, VBO;
    std::vector<unsigned int> TextureId;

    unsigned int loadTexture(const char* path);
};
