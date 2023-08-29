
#ifndef ENGINE_H
#define ENGINE_H

#ifdef __APPLE__
#define __CLEAR_TERMINAL system("clear")

#elif __linux__
#define __CLEAR_TERMINAL system("clear")

#else
#define __CLEAR_TERMINAL system("cls")
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Common.h"
#include "Utils.h"
// #include "core.h"
#include "Shader.h"
#include "Camera.h"
#include "Window.h"
// #include "mesh.h"
// #include "model.h"
// #include "scene.hpp"
// #include "drawable.hpp"
// #include "gui.h"
#include "rw_config.h"

#endif