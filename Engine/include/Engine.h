
#ifndef ENGINE_H
#define ENGINE_H

#ifdef __APPLE__
#define __CLEAR_TERMINAL system("clear")

#elif __linux__
#define __CLEAR_TERMINAL system("clear")

#else
#define __CLEAR_TERMINAL system("cls")
#endif

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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #include "core.h"
// #include "shader.hpp"
// #include "camera.hpp"
#include "Window.h"
// #include "mesh.h"
// #include "model.h"
// #include "scene.hpp"
// #include "drawable.hpp"
// #include "gui.h"
#include "rw_config.h"

#endif