#include "Window.h"
#include "Camera.h"

Window* Window::mInstance = nullptr;

Window::Window()
{
    mLastX = mWindowWidth / 2.0f;
    mLastY = mWindowHeight / 2.0f;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_SAMPLES, 4);
    // glfw window creation
    // --------------------
    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "LearnOpenGL", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

Window::~Window()
{
    glfwTerminate();
}

void Window::DestroyWindow()
{
    delete mInstance;
    mInstance = nullptr;
}

GLFWwindow* Window::getGlfwWindow()
{
    return mWindow;
}

void Window::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window* Window::getWindow()
{
    if (mInstance)
    {
        return mInstance;
    }

    mInstance = new Window();
    return mInstance;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// MARK: Waiting the camera
void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    CameraInstance* camera = CameraInstance::getCamera();
    Window* windowInstance = getWindow();
    if (windowInstance->isMouseEnalbe)
    {
        if (windowInstance->isFirstMouse)
        {
            windowInstance->mLastX = xpos;
            windowInstance->mLastY = ypos;
            windowInstance->isFirstMouse = false;
        }

        float xoffset = xpos - windowInstance->mLastX;
        float yoffset = windowInstance->mLastY - ypos; // reversed since y-coordinates go from bottom to top

        windowInstance->mLastX = xpos;
        windowInstance->mLastY = ypos;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }
    else
    {
        windowInstance->isFirstMouse = true;
    }
}

// MARK: Waiting the camera
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    CameraInstance* camera = CameraInstance::getCamera();
    camera->ProcessMouseScroll(yoffset);
}

// MARK: Waiting the camera
void Window::processInput()
{
    CameraInstance* camera = CameraInstance::getCamera();
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);

    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(CameraMovement::FORWARD, mDeltaTime);
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(CameraMovement::BACKWORD, mDeltaTime);
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(CameraMovement::LEFT, mDeltaTime);
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(CameraMovement::RIGHT, mDeltaTime);
    if (glfwGetKey(mWindow, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        isMouseEnalbe = false;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_M) == GLFW_PRESS)
    {
        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        isMouseEnalbe = true;
    }
}
