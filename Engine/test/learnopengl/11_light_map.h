#include "Engine.h"

// 11l_1 光照贴图实验1
namespace glx0111
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    bool firstMouse = false;
    float lastX = 400, lastY = 300;

    bool isMouseEnalbe = true;

    Camera mycamera(glm::vec3(0.1, 1.5, -3.5), glm::vec3(0.0f, 1.0f, 0.0f), 95, -17.5f);

    struct Material
    {
        glm::vec3 specular;
        float shininess;
    };

    struct Light
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    int main()
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

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImFont *font = io.Fonts->AddFontFromFileTTF(GET_RESOURCE_PATH("/fonts/kaiti_GB2312.ttf"), 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        // io.Fonts->GetGlyphRangesChineseFull();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // obj VAO init
        unsigned int objVBO, objVAO;
        glGenVertexArrays(1, &objVAO);
        glGenBuffers(1, &objVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(objVAO);

        glBindBuffer(GL_ARRAY_BUFFER, objVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // You can unbind the objVAO afterwards so other objVAO calls won't accidentally modify this objVAO, but this rarely happens. Modifying other
        // objVAOs requires a call to glBindVertexArray anyways so we generally don't unbind objVAOs (nor objVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered objVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // light VAO init
        unsigned int lightVBO, lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor lightVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered lightVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        stbi_set_flip_vertically_on_load(true);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载纹理图片
        int width, height, nrChannels;
        unsigned char *data = stbi_load(GET_RESOURCE_PATH("/imgs/container2.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        // unsigned int texture2;
        // glGenTextures(1, &texture2);
        // glBindTexture(GL_TEXTURE_2D, texture2);
        // // 为当前绑定的纹理对象设置环绕、过滤方式
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // data = stbi_load("./imgs/awesomeface.png", &width, &height, &nrChannels, 0);
        // if (data)
        // {
        //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //     glGenerateMipmap(GL_TEXTURE_2D);
        // }
        // else
        // {
        //     std::cout << "Failed to load texture1" << std::endl;
        // }
        // stbi_image_free(data);

        Shader objshader(GET_SHADER_PATH("/11/l1/ObjectVertex.vert"), GET_SHADER_PATH("/11/l1/ObjectFragment.frag"));
        Shader lightshader(GET_SHADER_PATH("/11/l1/LightVertex.vert"), GET_SHADER_PATH("/11/l1/LightFragment.frag"));

        objshader.use();
        objshader.setInt("material.diffuse", 0);
        glm::mat4 view = glm::mat4(1), model = glm::mat4(1), projection = glm::mat4(1);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);

        // glm::vec3 cubePositions[] = {
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        //     glm::vec3(-1.5f, -2.2f, -2.5f),
        //     glm::vec3(-3.8f, -2.0f, -12.3f),
        //     glm::vec3(2.4f, -0.4f, -3.5f),
        //     glm::vec3(-1.7f, 3.0f, -7.5f),
        //     glm::vec3(1.3f, -2.0f, -2.5f),
        //     glm::vec3(1.5f, 2.0f, -2.5f),
        //     glm::vec3(1.5f, 0.2f, -1.5f),
        //     glm::vec3(-1.3f, 1.0f, -1.5f)};

        // render loop
        // -----------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::vec3 objectColor(0.0f, 0.5f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1;
        float specularStrength = 0.5;
        float diffuseStrength = 1.0;
        Light light;
        light.position = glm::vec3(0.0f, 1.5f, 2.2f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        Material material;
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        material.shininess = 32.0f;
        while (!glfwWindowShouldClose(window))
        {
            // light move
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            // glActiveTexture(GL_TEXTURE1);
            // glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(objVAO);
            // 受光物体渲染
            objshader.use();
            view = mycamera.GetViewMatrix();
            objshader.setMat4("view", view);
            projection = glm::perspective(mycamera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
            objshader.setMat4("projection", projection);
            objshader.setVec3("light.position", light.position);
            objshader.setVec3("viewPos", mycamera.Position);
            model = glm::mat4(1);
            objshader.setMat4("model", model);
            light.diffuse = lightColor * glm::vec3(0.5f);    // decrease the influence
            light.ambient = light.diffuse * glm::vec3(0.2f); // low influence
            objshader.setVec3("light.ambient", light.ambient);
            objshader.setVec3("light.diffuse", light.diffuse);
            objshader.setVec3("light.specular", light.specular);

            // material properties
            objshader.setVec3("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
            objshader.setFloat("material.shininess", material.shininess);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 发光立方体渲染
            glBindVertexArray(lightVAO);
            lightshader.use();
            lightshader.setMat4("view", view);
            lightshader.setMat4("projection", projection);
            lightshader.setVec3("lightColor", lightColor);
            model = glm::mat4(1);
            model = glm::translate(model, light.position);
            model = glm::scale(model, glm::vec3(0.2f));
            lightshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // imgui
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("光照模型测试窗口");
                ImGui::SetWindowSize(ImVec2(300, 300));
                ImGui::SetWindowPos(ImVec2(0, 0));
                ImGui::ColorEdit3("灯光颜色", (float *)&lightColor);
                ImGui::TextWrapped("相机坐标 = (%f, %f, %f)", mycamera.Position.x, mycamera.Position.y, mycamera.Position.z);
                ImGui::TextWrapped("相机yaw角 = %f", mycamera.Yaw);
                ImGui::TextWrapped("相机pitch角 = %f", mycamera.Pitch);
                // ImGui::InputFloat3("material.ambient",(float*)&(material.ambient));
                // ImGui::InputFloat3("material.diffuse",(float*)&(material.diffuse));
                ImGui::InputFloat3("material.specular", (float *)&(material.specular));
                ImGui::InputFloat("material.shininess", &(material.shininess));
                ImGui::InputFloat3("light.ambient", (float *)&(light.ambient));
                ImGui::InputFloat3("light.diffuse", (float *)&(light.diffuse));
                ImGui::InputFloat3("light.position", (float *)&(light.position));
                ImGui::InputFloat3("light.specular", (float *)&(light.specular));
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &objVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &objVBO);
        glDeleteBuffers(1, &lightVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mycamera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mycamera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mycamera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mycamera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseEnalbe = false;
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseEnalbe = true;
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (isMouseEnalbe)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            mycamera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        mycamera.ProcessMouseScroll(yoffset);
    }
}
// 11l_2 光照贴图实验2（镜面贴图）
namespace glx0112
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    bool firstMouse = false;
    float lastX = 400, lastY = 300;

    bool isMouseEnalbe = true;

    Camera mycamera(glm::vec3(0.1, 1.5, -3.5), glm::vec3(0.0f, 1.0f, 0.0f), 95, -17.5f);

    struct Material
    {
        glm::vec3 specular;
        float shininess;
    };

    struct Light
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    int main()
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

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImFont *font = io.Fonts->AddFontFromFileTTF(GET_RESOURCE_PATH("/fonts/kaiti_GB2312.ttf"), 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        // io.Fonts->GetGlyphRangesChineseFull();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // obj VAO init
        unsigned int objVBO, objVAO;
        glGenVertexArrays(1, &objVAO);
        glGenBuffers(1, &objVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(objVAO);

        glBindBuffer(GL_ARRAY_BUFFER, objVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // You can unbind the objVAO afterwards so other objVAO calls won't accidentally modify this objVAO, but this rarely happens. Modifying other
        // objVAOs requires a call to glBindVertexArray anyways so we generally don't unbind objVAOs (nor objVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered objVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // light VAO init
        unsigned int lightVBO, lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor lightVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered lightVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        stbi_set_flip_vertically_on_load(true);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载纹理图片
        int width, height, nrChannels;
        unsigned char *data = stbi_load(GET_RESOURCE_PATH("/imgs/container2.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load(GET_RESOURCE_PATH("/imgs/container2_specular.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        Shader objshader(GET_SHADER_PATH("/11/l2/ObjectVertex.vert"), GET_SHADER_PATH("/11/l2/ObjectFragment.frag"));
        Shader lightshader(GET_SHADER_PATH("/11/l2/LightVertex.vert"), GET_SHADER_PATH("/11/l2/LightFragment.frag"));

        objshader.use();
        objshader.setInt("material.diffuse", 0);
        objshader.setInt("material.specular", 1);
        glm::mat4 view = glm::mat4(1), model = glm::mat4(1), projection = glm::mat4(1);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);

        // glm::vec3 cubePositions[] = {
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        //     glm::vec3(-1.5f, -2.2f, -2.5f),
        //     glm::vec3(-3.8f, -2.0f, -12.3f),
        //     glm::vec3(2.4f, -0.4f, -3.5f),
        //     glm::vec3(-1.7f, 3.0f, -7.5f),
        //     glm::vec3(1.3f, -2.0f, -2.5f),
        //     glm::vec3(1.5f, 2.0f, -2.5f),
        //     glm::vec3(1.5f, 0.2f, -1.5f),
        //     glm::vec3(-1.3f, 1.0f, -1.5f)};

        // render loop
        // -----------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::vec3 objectColor(0.0f, 0.5f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1;
        float specularStrength = 0.5;
        float diffuseStrength = 1.0;
        Light light;
        light.position = glm::vec3(0.0f, 1.5f, 2.2f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        Material material;
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        material.shininess = 32.0f;
        while (!glfwWindowShouldClose(window))
        {
            // light move
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(objVAO);
            // 受光物体渲染
            objshader.use();
            view = mycamera.GetViewMatrix();
            objshader.setMat4("view", view);
            projection = glm::perspective(mycamera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
            objshader.setMat4("projection", projection);
            objshader.setVec3("light.position", light.position);
            objshader.setVec3("viewPos", mycamera.Position);
            model = glm::mat4(1);
            objshader.setMat4("model", model);
            light.diffuse = lightColor * glm::vec3(0.5f);    // decrease the influence
            light.ambient = light.diffuse * glm::vec3(0.2f); // low influence
            objshader.setVec3("light.ambient", light.ambient);
            objshader.setVec3("light.diffuse", light.diffuse);
            objshader.setVec3("light.specular", light.specular);

            // material properties
            objshader.setVec3("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
            objshader.setFloat("material.shininess", material.shininess);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 发光立方体渲染
            glBindVertexArray(lightVAO);
            lightshader.use();
            lightshader.setMat4("view", view);
            lightshader.setMat4("projection", projection);
            lightshader.setVec3("lightColor", lightColor);
            model = glm::mat4(1);
            model = glm::translate(model, light.position);
            model = glm::scale(model, glm::vec3(0.2f));
            lightshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // imgui
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("光照模型测试窗口");
                ImGui::SetWindowSize(ImVec2(300, 300));
                ImGui::SetWindowPos(ImVec2(0, 0));
                ImGui::ColorEdit3("灯光颜色", (float *)&lightColor);
                ImGui::TextWrapped("相机坐标 = (%f, %f, %f)", mycamera.Position.x, mycamera.Position.y, mycamera.Position.z);
                ImGui::TextWrapped("相机yaw角 = %f", mycamera.Yaw);
                ImGui::TextWrapped("相机pitch角 = %f", mycamera.Pitch);
                // ImGui::InputFloat3("material.ambient",(float*)&(material.ambient));
                // ImGui::InputFloat3("material.diffuse",(float*)&(material.diffuse));
                ImGui::InputFloat3("material.specular", (float *)&(material.specular));
                ImGui::InputFloat("material.shininess", &(material.shininess));
                ImGui::InputFloat3("light.ambient", (float *)&(light.ambient));
                ImGui::InputFloat3("light.diffuse", (float *)&(light.diffuse));
                ImGui::InputFloat3("light.position", (float *)&(light.position));
                ImGui::InputFloat3("light.specular", (float *)&(light.specular));
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &objVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &objVBO);
        glDeleteBuffers(1, &lightVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mycamera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mycamera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mycamera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mycamera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseEnalbe = false;
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseEnalbe = true;
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (isMouseEnalbe)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            mycamera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        mycamera.ProcessMouseScroll(yoffset);
    }
}
// 11e_1 光照贴图习题1（反转贴图颜色）
namespace glxe0111
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    bool firstMouse = false;
    float lastX = 400, lastY = 300;

    bool isMouseEnalbe = true;

    Camera mycamera(glm::vec3(0.1, 1.5, -3.5), glm::vec3(0.0f, 1.0f, 0.0f), 95, -17.5f);

    struct Material
    {
        glm::vec3 specular;
        float shininess;
    };

    struct Light
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    int main()
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

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImFont *font = io.Fonts->AddFontFromFileTTF(GET_RESOURCE_PATH("/fonts/kaiti_GB2312.ttf"), 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        // io.Fonts->GetGlyphRangesChineseFull();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // obj VAO init
        unsigned int objVBO, objVAO;
        glGenVertexArrays(1, &objVAO);
        glGenBuffers(1, &objVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(objVAO);

        glBindBuffer(GL_ARRAY_BUFFER, objVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // You can unbind the objVAO afterwards so other objVAO calls won't accidentally modify this objVAO, but this rarely happens. Modifying other
        // objVAOs requires a call to glBindVertexArray anyways so we generally don't unbind objVAOs (nor objVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered objVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // light VAO init
        unsigned int lightVBO, lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor lightVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered lightVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        stbi_set_flip_vertically_on_load(true);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载纹理图片
        int width, height, nrChannels;
        unsigned char *data = stbi_load(GET_RESOURCE_PATH("/imgs/container2.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load(GET_RESOURCE_PATH("/imgs/container2_specular.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        Shader objshader(GET_SHADER_PATH("/11/e1/ObjectVertex.vert"), GET_SHADER_PATH("/11/e1/ObjectFragment.frag"));
        Shader lightshader(GET_SHADER_PATH("/11/e1/LightVertex.vert"), GET_SHADER_PATH("/11/e1/LightFragment.frag"));

        objshader.use();
        objshader.setInt("material.diffuse", 0);
        objshader.setInt("material.specular", 1);
        glm::mat4 view = glm::mat4(1), model = glm::mat4(1), projection = glm::mat4(1);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);

        // glm::vec3 cubePositions[] = {
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        //     glm::vec3(-1.5f, -2.2f, -2.5f),
        //     glm::vec3(-3.8f, -2.0f, -12.3f),
        //     glm::vec3(2.4f, -0.4f, -3.5f),
        //     glm::vec3(-1.7f, 3.0f, -7.5f),
        //     glm::vec3(1.3f, -2.0f, -2.5f),
        //     glm::vec3(1.5f, 2.0f, -2.5f),
        //     glm::vec3(1.5f, 0.2f, -1.5f),
        //     glm::vec3(-1.3f, 1.0f, -1.5f)};

        // render loop
        // -----------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::vec3 objectColor(0.0f, 0.5f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1;
        float specularStrength = 0.5;
        float diffuseStrength = 1.0;
        Light light;
        light.position = glm::vec3(0.0f, 1.5f, 2.2f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        Material material;
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        material.shininess = 32.0f;
        while (!glfwWindowShouldClose(window))
        {
            // light move
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(objVAO);
            // 受光物体渲染
            objshader.use();
            view = mycamera.GetViewMatrix();
            objshader.setMat4("view", view);
            projection = glm::perspective(mycamera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
            objshader.setMat4("projection", projection);
            objshader.setVec3("light.position", light.position);
            objshader.setVec3("viewPos", mycamera.Position);
            model = glm::mat4(1);
            objshader.setMat4("model", model);
            light.diffuse = lightColor * glm::vec3(0.5f);    // decrease the influence
            light.ambient = light.diffuse * glm::vec3(0.2f); // low influence
            objshader.setVec3("light.ambient", light.ambient);
            objshader.setVec3("light.diffuse", light.diffuse);
            objshader.setVec3("light.specular", light.specular);

            // material properties
            objshader.setVec3("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
            objshader.setFloat("material.shininess", material.shininess);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 发光立方体渲染
            glBindVertexArray(lightVAO);
            lightshader.use();
            lightshader.setMat4("view", view);
            lightshader.setMat4("projection", projection);
            lightshader.setVec3("lightColor", lightColor);
            model = glm::mat4(1);
            model = glm::translate(model, light.position);
            model = glm::scale(model, glm::vec3(0.2f));
            lightshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // imgui
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("光照模型测试窗口");
                ImGui::SetWindowSize(ImVec2(300, 300));
                ImGui::SetWindowPos(ImVec2(0, 0));
                ImGui::ColorEdit3("灯光颜色", (float *)&lightColor);
                ImGui::TextWrapped("相机坐标 = (%f, %f, %f)", mycamera.Position.x, mycamera.Position.y, mycamera.Position.z);
                ImGui::TextWrapped("相机yaw角 = %f", mycamera.Yaw);
                ImGui::TextWrapped("相机pitch角 = %f", mycamera.Pitch);
                // ImGui::InputFloat3("material.ambient",(float*)&(material.ambient));
                // ImGui::InputFloat3("material.diffuse",(float*)&(material.diffuse));
                ImGui::InputFloat3("material.specular", (float *)&(material.specular));
                ImGui::InputFloat("material.shininess", &(material.shininess));
                ImGui::InputFloat3("light.ambient", (float *)&(light.ambient));
                ImGui::InputFloat3("light.diffuse", (float *)&(light.diffuse));
                ImGui::InputFloat3("light.position", (float *)&(light.position));
                ImGui::InputFloat3("light.specular", (float *)&(light.specular));
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &objVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &objVBO);
        glDeleteBuffers(1, &lightVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mycamera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mycamera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mycamera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mycamera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseEnalbe = false;
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseEnalbe = true;
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (isMouseEnalbe)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            mycamera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        mycamera.ProcessMouseScroll(yoffset);
    }
}
// 11e_2 光照贴图习题2（彩色镜面贴图）
namespace glxe0112
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    bool firstMouse = false;
    float lastX = 400, lastY = 300;

    bool isMouseEnalbe = true;

    Camera mycamera(glm::vec3(0.1, 1.5, -3.5), glm::vec3(0.0f, 1.0f, 0.0f), 95, -17.5f);

    struct Material
    {
        glm::vec3 specular;
        float shininess;
    };

    struct Light
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    int main()
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

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImFont *font = io.Fonts->AddFontFromFileTTF(GET_RESOURCE_PATH("/fonts/kaiti_GB2312.ttf"), 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        // io.Fonts->GetGlyphRangesChineseFull();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // obj VAO init
        unsigned int objVBO, objVAO;
        glGenVertexArrays(1, &objVAO);
        glGenBuffers(1, &objVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(objVAO);

        glBindBuffer(GL_ARRAY_BUFFER, objVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // You can unbind the objVAO afterwards so other objVAO calls won't accidentally modify this objVAO, but this rarely happens. Modifying other
        // objVAOs requires a call to glBindVertexArray anyways so we generally don't unbind objVAOs (nor objVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered objVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // light VAO init
        unsigned int lightVBO, lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor lightVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered lightVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        stbi_set_flip_vertically_on_load(true);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载纹理图片
        int width, height, nrChannels;
        unsigned char *data = stbi_load(GET_RESOURCE_PATH("/imgs/container2.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load(GET_RESOURCE_PATH("/imgs/lighting_maps_specular_color.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        Shader objshader(GET_SHADER_PATH("/11/e2/ObjectVertex.vert"), GET_SHADER_PATH("/11/e2/ObjectFragment.frag"));
        Shader lightshader(GET_SHADER_PATH("/11/e2/LightVertex.vert"), GET_SHADER_PATH("/11/e2/LightFragment.frag"));

        objshader.use();
        objshader.setInt("material.diffuse", 0);
        objshader.setInt("material.specular", 1);
        glm::mat4 view = glm::mat4(1), model = glm::mat4(1), projection = glm::mat4(1);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);

        // glm::vec3 cubePositions[] = {
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        //     glm::vec3(-1.5f, -2.2f, -2.5f),
        //     glm::vec3(-3.8f, -2.0f, -12.3f),
        //     glm::vec3(2.4f, -0.4f, -3.5f),
        //     glm::vec3(-1.7f, 3.0f, -7.5f),
        //     glm::vec3(1.3f, -2.0f, -2.5f),
        //     glm::vec3(1.5f, 2.0f, -2.5f),
        //     glm::vec3(1.5f, 0.2f, -1.5f),
        //     glm::vec3(-1.3f, 1.0f, -1.5f)};

        // render loop
        // -----------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::vec3 objectColor(0.0f, 0.5f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1;
        float specularStrength = 0.5;
        float diffuseStrength = 1.0;
        Light light;
        light.position = glm::vec3(0.0f, 1.5f, 2.2f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        Material material;
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        material.shininess = 32.0f;
        while (!glfwWindowShouldClose(window))
        {
            // light move
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glBindVertexArray(objVAO);
            // 受光物体渲染
            objshader.use();
            view = mycamera.GetViewMatrix();
            objshader.setMat4("view", view);
            projection = glm::perspective(mycamera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
            objshader.setMat4("projection", projection);
            objshader.setVec3("light.position", light.position);
            objshader.setVec3("viewPos", mycamera.Position);
            model = glm::mat4(1);
            objshader.setMat4("model", model);
            light.diffuse = lightColor * glm::vec3(0.5f);    // decrease the influence
            light.ambient = light.diffuse * glm::vec3(0.2f); // low influence
            objshader.setVec3("light.ambient", light.ambient);
            objshader.setVec3("light.diffuse", light.diffuse);
            objshader.setVec3("light.specular", light.specular);

            // material properties
            objshader.setVec3("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
            objshader.setFloat("material.shininess", material.shininess);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 发光立方体渲染
            glBindVertexArray(lightVAO);
            lightshader.use();
            lightshader.setMat4("view", view);
            lightshader.setMat4("projection", projection);
            lightshader.setVec3("lightColor", lightColor);
            model = glm::mat4(1);
            model = glm::translate(model, light.position);
            model = glm::scale(model, glm::vec3(0.2f));
            lightshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // imgui
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("光照模型测试窗口");
                ImGui::SetWindowSize(ImVec2(300, 300));
                ImGui::SetWindowPos(ImVec2(0, 0));
                ImGui::ColorEdit3("灯光颜色", (float *)&lightColor);
                ImGui::TextWrapped("相机坐标 = (%f, %f, %f)", mycamera.Position.x, mycamera.Position.y, mycamera.Position.z);
                ImGui::TextWrapped("相机yaw角 = %f", mycamera.Yaw);
                ImGui::TextWrapped("相机pitch角 = %f", mycamera.Pitch);
                // ImGui::InputFloat3("material.ambient",(float*)&(material.ambient));
                // ImGui::InputFloat3("material.diffuse",(float*)&(material.diffuse));
                ImGui::InputFloat3("material.specular", (float *)&(material.specular));
                ImGui::InputFloat("material.shininess", &(material.shininess));
                ImGui::InputFloat3("light.ambient", (float *)&(light.ambient));
                ImGui::InputFloat3("light.diffuse", (float *)&(light.diffuse));
                ImGui::InputFloat3("light.position", (float *)&(light.position));
                ImGui::InputFloat3("light.specular", (float *)&(light.specular));
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &objVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &objVBO);
        glDeleteBuffers(1, &lightVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mycamera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mycamera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mycamera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mycamera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseEnalbe = false;
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseEnalbe = true;
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (isMouseEnalbe)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            mycamera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        mycamera.ProcessMouseScroll(yoffset);
    }
}
// 11e_3 光照贴图习题3（放射光贴图）
namespace glxe0113
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    bool firstMouse = false;
    float lastX = 400, lastY = 300;

    bool isMouseEnalbe = true;

    Camera mycamera(glm::vec3(0.1, 1.5, -3.5), glm::vec3(0.0f, 1.0f, 0.0f), 95, -17.5f);

    struct Material
    {
        glm::vec3 specular;
        float shininess;
    };

    struct Light
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    int main()
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

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImFont *font = io.Fonts->AddFontFromFileTTF(GET_RESOURCE_PATH("/fonts/kaiti_GB2312.ttf"), 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon();
        // io.Fonts->GetGlyphRangesChineseFull();

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

        // obj VAO init
        unsigned int objVBO, objVAO;
        glGenVertexArrays(1, &objVAO);
        glGenBuffers(1, &objVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(objVAO);

        glBindBuffer(GL_ARRAY_BUFFER, objVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // You can unbind the objVAO afterwards so other objVAO calls won't accidentally modify this objVAO, but this rarely happens. Modifying other
        // objVAOs requires a call to glBindVertexArray anyways so we generally don't unbind objVAOs (nor objVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered objVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // light VAO init
        unsigned int lightVBO, lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor lightVBOs) when it's not directly necessary.
        glBindVertexArray(0);
        // note that this is allowed, the call to glVertexAttribPointer registered lightVBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        stbi_set_flip_vertically_on_load(true);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 加载纹理图片
        int width, height, nrChannels;
        unsigned char *data = stbi_load(GET_RESOURCE_PATH("/imgs/container2.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture1" << std::endl;
        }
        stbi_image_free(data);

        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load(GET_RESOURCE_PATH("/imgs/container2_specular.png"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture2" << std::endl;
        }
        stbi_image_free(data);

        unsigned int texture3;
        glGenTextures(1, &texture3);
        glBindTexture(GL_TEXTURE_2D, texture3);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        data = stbi_load(GET_RESOURCE_PATH("/imgs/matrix.jpeg"), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture3" << std::endl;
        }
        stbi_image_free(data);

        Shader objshader(GET_SHADER_PATH("/11/e3/ObjectVertex.vert"), GET_SHADER_PATH("/11/e3/ObjectFragment.frag"));
        Shader lightshader(GET_SHADER_PATH("/11/e3/LightVertex.vert"), GET_SHADER_PATH("/11/e3/LightFragment.frag"));

        objshader.use();
        objshader.setInt("material.diffuse", 0);
        objshader.setInt("material.specular", 1);
        objshader.setInt("material.emission", 2);
        glm::mat4 view = glm::mat4(1), model = glm::mat4(1), projection = glm::mat4(1);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

        glEnable(GL_DEPTH_TEST);

        // glm::vec3 cubePositions[] = {
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        //     glm::vec3(-1.5f, -2.2f, -2.5f),
        //     glm::vec3(-3.8f, -2.0f, -12.3f),
        //     glm::vec3(2.4f, -0.4f, -3.5f),
        //     glm::vec3(-1.7f, 3.0f, -7.5f),
        //     glm::vec3(1.3f, -2.0f, -2.5f),
        //     glm::vec3(1.5f, 2.0f, -2.5f),
        //     glm::vec3(1.5f, 0.2f, -1.5f),
        //     glm::vec3(-1.3f, 1.0f, -1.5f)};

        // render loop
        // -----------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::vec3 objectColor(0.0f, 0.5f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1;
        float specularStrength = 0.5;
        float diffuseStrength = 1.0;
        Light light;
        light.position = glm::vec3(0.0f, 1.5f, 2.2f);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        Material material;
        material.specular = glm::vec3(0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        material.shininess = 32.0f;
        while (!glfwWindowShouldClose(window))
        {
            // light move
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, texture3);
            glBindVertexArray(objVAO);
            // 受光物体渲染
            objshader.use();
            view = mycamera.GetViewMatrix();
            objshader.setMat4("view", view);
            projection = glm::perspective(mycamera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
            objshader.setMat4("projection", projection);
            objshader.setVec3("light.position", light.position);
            objshader.setVec3("viewPos", mycamera.Position);
            model = glm::mat4(1);
            objshader.setMat4("model", model);
            light.diffuse = lightColor * glm::vec3(0.5f);    // decrease the influence
            light.ambient = light.diffuse * glm::vec3(0.2f); // low influence
            objshader.setVec3("light.ambient", light.ambient);
            objshader.setVec3("light.diffuse", light.diffuse);
            objshader.setVec3("light.specular", light.specular);

            // material properties
            objshader.setVec3("material.specular", material.specular); // specular lighting doesn't have full effect on this object's material
            objshader.setFloat("material.shininess", material.shininess);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // 发光立方体渲染
            glBindVertexArray(lightVAO);
            lightshader.use();
            lightshader.setMat4("view", view);
            lightshader.setMat4("projection", projection);
            lightshader.setVec3("lightColor", lightColor);
            model = glm::mat4(1);
            model = glm::translate(model, light.position);
            model = glm::scale(model, glm::vec3(0.2f));
            lightshader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // imgui
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                ImGui::Begin("光照模型测试窗口");
                ImGui::SetWindowSize(ImVec2(300, 300));
                ImGui::SetWindowPos(ImVec2(0, 0));
                ImGui::ColorEdit3("灯光颜色", (float *)&lightColor);
                ImGui::TextWrapped("相机坐标 = (%f, %f, %f)", mycamera.Position.x, mycamera.Position.y, mycamera.Position.z);
                ImGui::TextWrapped("相机yaw角 = %f", mycamera.Yaw);
                ImGui::TextWrapped("相机pitch角 = %f", mycamera.Pitch);
                // ImGui::InputFloat3("material.ambient",(float*)&(material.ambient));
                // ImGui::InputFloat3("material.diffuse",(float*)&(material.diffuse));
                ImGui::InputFloat3("material.specular", (float *)&(material.specular));
                ImGui::InputFloat("material.shininess", &(material.shininess));
                ImGui::InputFloat3("light.ambient", (float *)&(light.ambient));
                ImGui::InputFloat3("light.diffuse", (float *)&(light.diffuse));
                ImGui::InputFloat3("light.position", (float *)&(light.position));
                ImGui::InputFloat3("light.specular", (float *)&(light.specular));
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &objVAO);
        glDeleteVertexArrays(1, &lightVAO);
        glDeleteBuffers(1, &objVBO);
        glDeleteBuffers(1, &lightVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mycamera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mycamera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mycamera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mycamera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseEnalbe = false;
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseEnalbe = true;
        }
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        if (isMouseEnalbe)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;

            mycamera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        mycamera.ProcessMouseScroll(yoffset);
    }
}
