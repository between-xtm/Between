#include "Window.h"

Window *Window::mInstance = nullptr;

Window::Window()
{
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
    mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "LearnOpenGL", NULL, NULL);
    if (mWindow == NULL)
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
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window* Window::getWindow()
{
    if(mInstance)
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
    
}

// MARK: Waiting the camera
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}

// MARK: Waiting the camera
void Window::processInput()
{
    
}
