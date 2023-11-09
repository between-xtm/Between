#pragma once

#include "Common.h"

class Shader;

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void setVertex(std::vector<Vertex> ver) { vertices = ver; }
    void addVertex(Vertex ver) { vertices.emplace_back(ver); }
    void setIndices(std::vector<unsigned int> ind) { indices = ind; }
    void addIndices(unsigned int ind) { indices.emplace_back(ind); }
    void setTexture(std::vector<Texture> tex) { textures = tex; }
    void addTexture(Texture tex) { textures.emplace_back(tex); }

    std::vector<Vertex> getVertex() { return vertices; }
    std::vector<unsigned int> getIndices() { return indices; }
    std::vector<Texture> getTexture() { return textures; }
    unsigned int getVAO() { return VAO; }
    Vertex getVert(int i);
    unsigned int getIndices(int i);
    Texture getTexture(int i);

    void Draw(Shader& shader);

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
