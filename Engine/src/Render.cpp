#include "Render.h"
// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Render::Draw()
{
    // UpdateCamera();
    shader->use();
    glBindVertexArray(VAO);
    if (drawlayout & (TextureDrawlayout))
    {
        for (int i = 0; i < TextureId.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, TextureId[i]);
        }
    }
    if (drawlayout & (NeedSkyBoxTexture))
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, SkyboxTextureID);
        glDepthFunc(GL_LEQUAL);
    }

    if (drawlayout & (InstanceDrawlayout))
    {
        glDrawArraysInstanced(drawTypes, 0, vn, instanceNum);
    }
    else
    {
        glDrawArrays(drawTypes, 0, vn);
    }
    glDepthFunc(GL_LESS);
    glUseProgram(0);
}

Render::~Render()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteTextures(1, &TextureID);
    for (int i = 0; i < TextureId.size(); i++)
    {
        glDeleteTextures(1, &TextureId[i]);
    }

    delete shader;
}

Render* Render::SetShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    if (shader != nullptr)
    {
        delete shader;
    }

    shader = new Shader(vertexPath, fragmentPath, geometryPath);
    return this;
}

Render* Render::SetModel(glm::mat4 model)
{
    shader->use();
    shader->setMat4("model", model);
    glUseProgram(0);
    return this;
}

Render* Render::SetTextureId(const char* texturePath, const char* uniformName)
{
    drawlayout = static_cast<DrawLayout>(drawlayout | TextureDrawlayout);
    unsigned int tmp;
    tmp = loadTexture(texturePath);
    TextureId.push_back(tmp);
    shader->use();
    if (uniformName != nullptr)
    {
        shader->setInt(uniformName, TextureId.size() - 1);
    }
    glUseProgram(0);

    return this;
}

Render* Render::SetDrawlayout(unsigned int dl)
{
    drawlayout = static_cast<DrawLayout>(dl);
    return this;
}

Render* Render::SetDrawTypes(unsigned int dt)
{
    drawTypes = static_cast<DrawLayout>(dt);
    return this;
}

Shader* Render::GetShader()
{
    return shader;
}

Render* Render::SetVertex(void* v, VertexLayout vertexlayout, int vsize)
{
    vt = vertexlayout;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vsize, v, GL_STATIC_DRAW);
    switch (vt)
    {
    case VertexLayout::VertexTexcoordlayout:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        vn = vsize / (sizeof(float) * 5);
        break;
    case VertexLayout::Vertexlayout:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        vn = vsize / (sizeof(float) * 3);
        break;
    case VertexLayout::D2VertexTexcoordlayout:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        vn = vsize / (sizeof(float) * 4);

        break;
    default:
        break;
    }
    glBindVertexArray(0);
    return this;
}

Render* Render::SetVertexLayout(VertexLayout _vt)
{
    vt = _vt;
    return this;
}

Render* Render::SetVertexNum(int _vn)
{
    vn = _vn;
    return this;
}

Render* Render::SetVertexFromData(std::string dataPath, unsigned int iv)
{
    float positions[256] = {0};
    float normals[256] = {0};
    float texcoord[256] = {0};
    float instance[32768] = {0};
    std::string positionsPath, normalsPath, texcoordPath, instancePath;
    positionsPath = dataPath + "positions.txt";
    normalsPath = dataPath + "normals.txt";
    texcoordPath = dataPath + "texcoord.txt";
    instancePath = dataPath + "instance.txt";

    std::ifstream positionsIn(positionsPath.c_str());
    std::ifstream normalsIn(normalsPath.c_str());
    std::ifstream texcoordIn(texcoordPath.c_str());
    std::ifstream instanceIn(instancePath.c_str());
    unsigned int i = 0;
    float tmp = 0.0f;
    while (positionsIn.is_open() && positionsIn >> tmp)
    {
        positions[i] = tmp;
        i++;
    }

    i = 0;
    tmp = 0.0f;
    while (normalsIn.is_open() && normalsIn >> tmp)
    {
        normals[i] = tmp;
        i++;
    }

    i = 0;
    tmp = 0.0f;
    while (texcoordIn.is_open() && texcoordIn >> tmp)
    {
        texcoord[i] = tmp;
        i++;
    }
    i = 0;
    tmp = 0.0f;
    while (drawlayout & (InstanceDrawlayout) && instanceIn.is_open() && instanceIn >> tmp)
    {
        instance[i] = tmp;
        i++;
    }

    positionsIn.close();
    normalsIn.close();
    texcoordIn.close();
    instanceIn.close();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned long subOffset = 0;
    switch (vt)
    {
    case VertexLayout::Vertexlayout:
        subOffset = vn * sizeof(float) * 3;
        glBufferData(GL_ARRAY_BUFFER, vn * sizeof(float) * 3 + iv * sizeof(float) * instanceNum, nullptr,
                     GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vn, positions);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        break;
    case VertexLayout::VertexNormallayout:
        subOffset = vn * sizeof(float) * 3 + vn * sizeof(float) * 3;
        glBufferData(
            GL_ARRAY_BUFFER, vn * sizeof(float) * 3 + vn * sizeof(float) * 3 + iv * sizeof(float) * instanceNum,
            nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vn, positions);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vn, 3 * sizeof(float) * vn, normals);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float) * vn));
        break;
    case VertexLayout::VertexTexcoordlayout:
        subOffset = vn * sizeof(float) * 3 + vn * sizeof(float) * 2;
        glBufferData(
            GL_ARRAY_BUFFER, vn * sizeof(float) * 3 + vn * sizeof(float) * 2 + iv * sizeof(float) * instanceNum,
            nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vn, positions);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vn, 2 * sizeof(float) * vn, texcoord);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(3 * sizeof(float) * vn));
        break;
    case VertexLayout::VertexNormalTexcoordlayout:
        subOffset = vn * sizeof(float) * 3 + vn * sizeof(float) * 3 + vn * sizeof(float) * 2;
        glBufferData(
            GL_ARRAY_BUFFER,
            vn * sizeof(float) * 3 + vn * sizeof(float) * 3 + vn * sizeof(float) * 2 + iv * sizeof(float) * instanceNum,
            nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vn, positions);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vn, 3 * sizeof(float) * vn, normals);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vn + 3 * sizeof(float) * vn, 2 * sizeof(float) * vn,
                        texcoord);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float) * vn));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(3 * sizeof(float) * vn + 3 * sizeof(float) * vn));
        break;
    default:
        break;
    }
    if (drawlayout & (InstanceDrawlayout) && iv)
    {
        glBufferSubData(GL_ARRAY_BUFFER, subOffset, iv * sizeof(float) * instanceNum, instance);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(
            3, iv, GL_FLOAT, GL_FALSE, iv * sizeof(float), (void*)(subOffset));
        glVertexAttribDivisor(3, 1);
    }

    glBindVertexArray(0);
    return this;
}

void Render::UpdateCamera()
{
    if (glGetUniformBlockIndex(shader->getProgram(), "CameraMatrices") == GL_INVALID_INDEX)
    {
        CameraInstance* camera = CameraInstance::getCamera();
        glm::mat4 view = camera->getViewMatrix();
        // glm::mat4 projection = camera->getPerspective();
        glm::mat4 projection = camera->getOrtho();
        shader->use();
        if (drawlayout & (CamerPositionInside))
        {
            shader->setVec3("cameraPos", camera->getPosition());
        }

        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        glUseProgram(0);
    }
}

unsigned int Render::loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Render::DeleteAllTextures()
{
    for (int i = 0; i < TextureId.size(); i++)
    {
        glDeleteTextures(1, &TextureId[i]);
    }
    TextureId.swap(std::vector<unsigned int>());
}

