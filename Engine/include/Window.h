#pragma once
#include "Common.h"

class Window
{
private:
    GLFWwindow* mWindow = nullptr;
    static Window* mInstance;
    Window();
    Window& operator=(const Window&);
    bool isMouseEnalbe = true;
    bool isFirstMouse = true;

    unsigned int mWindowWidth = 1920;
    unsigned int mWindowHeight = 1080;
    float mLastX;
    float mLastY;

    float mDeltaTime = 0.0;
    float mLastFrame = 0.0;
    
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    ~Window();

    static void DestroyWindow();

    GLFWwindow* getGlfwWindow();

    static void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

    static Window* getWindow();

    float getWindowWidth()
    {
        return mWindowWidth;
    }

    inline float getWindowHeight()
    {
        return mWindowHeight;
    }

    void processInput();

    bool WindowShouldClose()
    {
        return glfwWindowShouldClose(mWindow);
    }

    void SwapBufferAndPollEvents()
    {
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    void UpdateDeltaTime()
    {
        mDeltaTime = glfwGetTime() - mLastFrame;
        mLastFrame = glfwGetTime();
    }
};
