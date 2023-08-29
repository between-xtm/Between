#include "Engine.h"

 int main()
    {
        Window* window = Window::getWindow();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  // right
            0.0f, 0.5f, 0.0f    // top
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        std::cout << getFilePath() << std::endl;

        Shader myshader(GET_SHADER_WITH_CURRENT_PATH("..\\..\\Engine\\resource\\shaders\\3\\l1\\vertex.vert"), "..\\..\\Engine\\resource\\shaders\\3\\l1\\fragment.frag");
        // render loop
        // -----------
        while (!glfwWindowShouldClose(window->getGlfwWindow()))
        {

            // render
            // ------
            // processInput(window->getGlfwWindow());
            window->processInput();
            window->Clear(0,0,0,1);
            glBindVertexArray(VAO);
            myshader.use();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            window->SwapBufferAndPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }
