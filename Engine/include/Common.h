
#pragma once
#include<imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define BIT(x) (1 << x)

struct Vertex
{
    glm::vec3 Position = glm::vec3(-1,-1,-1);
    glm::vec3 Normal = glm::vec3(-1,-1,-1);
    glm::vec2 TexCoords= glm::vec2(-1,-1);
    glm::vec3 Tangent = glm::vec3(-1,-1,-1);
    glm::vec3 Bitangent = glm::vec3(-1,-1,-1);
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};