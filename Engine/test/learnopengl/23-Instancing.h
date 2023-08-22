#include "Engine.h"

// 未使用实例化
namespace glx0231
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);

        Drawable *drawable = (new Drawable())
                                 ->SetVertexNum(6)
                                 ->SetVertexLayout(VertexNormallayout)
                                 ->SetVertexFromData(GET_RESOURCE_PATH("/data/23/l1/"))
                                 ->SetShader(GET_SHADER_PATH("/23/l1/ObjectVertex.vert"), GET_SHADER_PATH("/23/l1/ObjectFragment.frag"))
                                 ->SetModel(glm::mat4(1));
        glm::vec3 translations[100];
        int index = 0;
        float offset = 0.1f;
        for (int y = -10; y < 10; y += 2)
        {
            for (int x = -10; x < 10; x += 2)
            {
                glm::vec3 translation;
                translation.x = (float)x / 10.0f + offset;
                translation.y = (float)y / 10.0f + offset;
                translation.z = 0;
                translations[index++] = translation;
            }
        }

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            camera->UpdateUniform();
            // input
            // -----
            window->processInput();

            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("实例化");
                ImGui::End();
            }

            mGUI::RenderGUI();
            for (int i = 0; i < 100; i++)
            {
                drawable->GetShader()->setVec3("offset", translations[i]);
                drawable->Draw();
            }

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}
// 使用实例化
namespace glx0232
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);

        Drawable *drawable = (new Drawable())
                                 ->SetVertexNum(6)
                                 ->SetDrawInstance(100)
                                 ->SetVertexLayout(VertexNormallayout)
                                 ->SetVertexFromData(GET_RESOURCE_PATH("/data/23/l1/"))
                                 ->SetShader(GET_SHADER_PATH("/23/l2/ObjectVertex.vert"), GET_SHADER_PATH("/23/l2/ObjectFragment.frag"))
                                 ->SetModel(glm::mat4(1));
        glm::vec3 translations[100];
        int index = 0;
        float offset = 0.1f;
        for (int y = -10; y < 10; y += 2)
        {
            for (int x = -10; x < 10; x += 2)
            {
                glm::vec3 translation;
                translation.x = (float)x / 10.0f + offset;
                translation.y = (float)y / 10.0f + offset;
                translation.z = 0;
                translations[index++] = translation;
            }
        }
        for (unsigned int i = 0; i < 100; i++)
        {
            stringstream ss;
            string index;
            ss << i;
            index = ss.str();
            drawable->GetShader()->setVec3(("offsets[" + index + "]").c_str(), translations[i]);
        }

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            camera->UpdateUniform();
            // input
            // -----
            window->processInput();

            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("实例化");
                ImGui::Text("FPS:%f", 1 / window->deltaTime);
                ImGui::End();
            }

            mGUI::RenderGUI();

            drawable->Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// 实例化数组
namespace glx0233
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);
        SkyBox skybox;

        Drawable *drawable = (new Drawable())
                                 ->SetVertexNum(6)
                                 ->SetDrawInstance(10000)
                                 ->SetVertexLayout(VertexNormallayout)
                                 ->SetVertexFromData(GET_RESOURCE_PATH("/data/23/l3/"), 2)
                                 ->SetShader(GET_SHADER_PATH("/23/l3/ObjectVertex.vert"), GET_SHADER_PATH("/23/l3/ObjectFragment.frag"))
                                 ->SetModel(glm::mat4(1));

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            camera->UpdateUniform();
            // input
            // -----
            window->processInput();

            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin(u8"实例化");
                ImGui::Text("FPS:%f", 1 / window->deltaTime);
                ImGui::End();
            }

            mGUI::RenderGUI();

            drawable->Draw();
            skybox.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// 实例化行星模型试验(未使用实例化渲染)
namespace glx0234
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();
        camera->SetMovementSpeed(2 * SPEED);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable *planet = (new mModel())
                               ->Setmodel(GET_RESOURCE_PATH("/models/planet/planet.obj"))
                               ->SetShader(GET_SHADER_PATH("/23/l4/PlanetVertex.vert"), GET_SHADER_PATH("/23/l4/PlanetFragment.frag"))
                               ->SetModel(glm::mat4(1));
        Drawable *rock = (new mModel())
                             ->Setmodel(GET_RESOURCE_PATH("/models/rock/rock.obj"))
                             ->SetShader(GET_SHADER_PATH("/23/l4/RockVertex.vert"), GET_SHADER_PATH("/23/l4/RockFragment.frag"))
                             ->SetModel(glm::mat4(1));

        unsigned int amount = 20000;
        glm::mat4 *modelMatrices;
        modelMatrices = new glm::mat4[amount];
        srand(glfwGetTime()); // 初始化随机种子
        float radius = 50.0;
        float offset = 25.0f;
        for (unsigned int i = 0; i < amount; i++)
        {
            glm::mat4 model;
            // 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
            float angle = (float)i / (float)amount * 360.0f;
            float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float x = sin(angle) * radius + displacement;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float y = displacement * 0.2f; // 让行星带的高度比x和z的宽度要小
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float z = cos(angle) * radius + displacement;
            model = glm::translate(model, glm::vec3(x, y, z));

            // 2. 缩放：在 0.05 和 0.25f 之间缩放
            float scale = (rand() % 20) / 100.0f + 0.05;
            model = glm::scale(model, glm::vec3(scale));

            // 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
            float rotAngle = (rand() % 360);
            model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

            // 4. 添加到矩阵的数组中
            modelMatrices[i] = model;
        }

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        planet->SetModel(model);

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            camera->UpdateUniform();
            // input
            // -----
            window->processInput();

            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin(u8"实例化");
                ImGui::Text("FPS:%f", 1 / window->deltaTime);
                ImGui::Text(u8"模型数%d", amount);
                ImGui::End();
            }

            mGUI::RenderGUI();

            planet->Draw();
            // 绘制小行星
            for (unsigned int i = 0; i < amount; i++)
            {
                rock->SetModel(modelMatrices[i]);
                rock->Draw();
            }

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        delete planet;
        delete rock;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// 实例化行星模型试验(使用实例化渲染)
namespace glx0235
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();
        camera->SetMovementSpeed(2 * SPEED);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable *planet = (new mModel())
                               ->Setmodel(GET_RESOURCE_PATH("/models/planet/planet.obj"))
                               ->SetShader(GET_SHADER_PATH("/23/l5/PlanetVertex.vert"), GET_SHADER_PATH("/23/l5/PlanetFragment.frag"))
                               ->SetModel(glm::mat4(1));
        Drawable *rock = (new mModel())\
                            ->Setmodel(GET_RESOURCE_PATH("/models/rock/rock.obj"))\
                             ->SetDrawInstance(20000)\
                             ->SetShader(GET_SHADER_PATH("/23/l5/RockVertex.vert"), GET_SHADER_PATH("/23/l5/RockFragment.frag"))\
                             ->SetModel(glm::mat4(1));

        unsigned int amount = 1000000;
        glm::mat4 *modelMatrices;
        modelMatrices = new glm::mat4[amount];
        srand(glfwGetTime()); // 初始化随机种子
        float radius = 150.0;
        float offset = 100.0f;
        for (unsigned int i = 0; i < amount; i++)
        {
            glm::mat4 model;
            // 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
            float angle = (float)i / (float)amount * 360.0f;
            float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float x = sin(angle) * radius + displacement;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float y = displacement * 0.2f; // 让行星带的高度比x和z的宽度要小
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float z = cos(angle) * radius + displacement;
            model = glm::translate(model, glm::vec3(x, y, z));

            // 2. 缩放：在 0.05 和 0.25f 之间缩放
            float scale = (rand() % 20) / 100.0f + 0.05;
            model = glm::scale(model, glm::vec3(scale));

            // 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
            float rotAngle = (rand() % 360);
            model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

            // 4. 添加到矩阵的数组中
            modelMatrices[i] = model;
        }

        // 顶点缓冲对象
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        for (unsigned int i = 0; i < ((mModel*)rock)->Getmodel()->meshes.size(); i++)
        {
            unsigned int VAO = ((mModel*)rock)->Getmodel()->meshes[i].VAO;
            glBindVertexArray(VAO);
            // 顶点属性
            GLsizei vec4Size = sizeof(glm::vec4);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(2 * vec4Size));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void *)(3 * vec4Size));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        planet->SetModel(model);

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            camera->UpdateUniform();
            // input
            // -----
            window->processInput();

            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin(u8"实例化");
                ImGui::Text(u8"FPS:%f", 1 / window->deltaTime);
                ImGui::Text(u8"模型数%d", amount);
                ImGui::End();
            }

            mGUI::RenderGUI();

            planet->Draw();
            // 绘制小行星
            rock->Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        delete planet;
        delete rock;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}