#include"Engine.h"
namespace glx0241
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // 开启多重采样MSAA
        glEnable(GL_MULTISAMPLE);



        Drawable *cube = (new Cube())->SetShader(GET_SHADER_PATH("/24/l1/ObjectVertexShader.vert"), GET_SHADER_PATH("/24/l1/ObjectFragmentShader.frag"))->SetModel(glm::mat4(1));
        
        Object *obj = new Object(glm::vec3(0, 0, 0));

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

            // render
            // ------
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("抗锯齿");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::InputFloat3("Objet scale", (float *)&(obj->Scale));
                ImGui::End();
            }

            mGUI::RenderGUI();

            cube->Draw();
            

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }
}
namespace glx0242
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // 开启多重采样MSAA
        glEnable(GL_MULTISAMPLE);



        Drawable *cube = (new Cube())->SetShader(GET_SHADER_PATH("/24/l1/ObjectVertexShader.vert"), GET_SHADER_PATH("/24/l1/ObjectFragmentShader.frag"))->SetModel(glm::mat4(1));
        
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(0, 0, 0));

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

            // render
            // ------
            fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("抗锯齿");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::InputFloat3("Objet scale", (float *)&(obj->Scale));
                ImGui::End();
            }

            mGUI::RenderGUI();

            cube->Draw();
            
            fbo.SetMainFrameBuffer();
            fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }
}
