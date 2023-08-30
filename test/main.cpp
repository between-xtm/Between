#include "Engine.h"

 int main()
    {
        Window* window = Window::getWindow();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  // right
            0.0f, 0.5f, 0.0f    // top
        };

        Render* render = new Render();
        render->SetVertex(vertices, VertexLayout::Vertexlayout, sizeof(vertices));
        std::cout << getFilePath() << std::endl;
        render->SetShader("..\\..\\Engine\\resource\\shaders\\3\\l1\\vertex.vert", "..\\..\\Engine\\resource\\shaders\\3\\l1\\fragment.frag");
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window->getGlfwWindow()))
        {

            // render
            // ------
            window->processInput();
            window->Clear(0,0,0,1);
            render->Draw();
            window->SwapBufferAndPollEvents();
        }
     
        
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
