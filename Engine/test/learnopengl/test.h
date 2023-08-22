#include"Engine.h"

// 绘制物体网格测试
namespace test1
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);
        
        // Drawable* drawable =  (new mModel())->SetShader("./22/l3/ObjectVertex.vert", "./22/l3/ObjectFragment.frag", "./22/l3/ObjectGeometry.gs")->SetModle(glm::mat4(1));
        Drawable* drawable =  (new mModel());
        Shader* ss = new Shader(GET_SHADER_PATH("/test/ModelWithLight/ObjectVertex.vert"), GET_SHADER_PATH("/test/ModelWithLight/ObjectFragment.frag"));
        ss->setMat4("model", glm::mat4(1));
        Plane plane;
        SkyBox skybox;

        float ex = 0.0f;

        // glPointSize(200);
        
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
                ImGui::Begin("法线可视化");
                ImGui::End();
            }

            mGUI::RenderGUI();
            skybox.Draw();
            drawable->Draw(ss);
            // drawable->Draw();
            plane.Draw();
            
            

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
// 测试光源
namespace test2
{
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);
        
        // Drawable* drawable =  (new mModel())->SetShader("./22/l3/ObjectVertex.vert", "./22/l3/ObjectFragment.frag", "./22/l3/ObjectGeometry.gs")->SetModle(glm::mat4(1));
        Drawable* drawable =  (new mModel());
        Shader* ss = new Shader(GET_SHADER_PATH("/test/1/ObjectVertex.vert"), GET_SHADER_PATH("/test/1/ObjectFragment.frag"), GET_SHADER_PATH("/test/1/ObjectGeometry.gs"));
        ss->setMat4("model", glm::mat4(1));
        Plane plane;
        SkyBox skybox;

        float ex = 0.0f;

        // glPointSize(200);
        
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
                ImGui::Begin("法线可视化");
                ImGui::End();
            }

            mGUI::RenderGUI();
            skybox.Draw();
            drawable->Draw(ss);
            drawable->Draw();
            plane.Draw();
            
            

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