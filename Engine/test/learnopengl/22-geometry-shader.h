#include"Engine.h"

namespace glx0221
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(Vertexlayout)\
                                ->SetDrawTypes(GL_POINTS)\
                                ->SetVertexNum(4)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/22/l1/"))\
                                ->SetShader(GET_SHADER_PATH("/22/l1/ObjectVertex.vert"), GET_SHADER_PATH("/22/l1/ObjectFragment.frag"), GET_SHADER_PATH("/22/l1/ObjectGeometry.gs"))\
                                ->SetModel(glm::mat4(1));

        glPointSize(200);
        
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
                ImGui::Begin("myGUI");
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

namespace glx0222
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPointSize(200);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(VertexNormallayout)\
                                ->SetDrawTypes(GL_POINTS)\
                                ->SetVertexNum(4)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/22/l2/"))\
                                ->SetShader(GET_SHADER_PATH("/22/l2/ObjectVertex.vert"), GET_SHADER_PATH("/22/l2/ObjectFragment.frag"), GET_SHADER_PATH("/22/l2/ObjectGeometry.gs"))\
                                ->SetModel(glm::mat4(1));

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
                ImGui::Begin("myGUI");
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

namespace glx0223
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
        Shader* ss = GU_EXPLOR_SHADER;
        
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
                ImGui::Begin("爆破");
                ImGui::DragFloat("爆破", &ex, 0.01, 0, 10);
                ImGui::End();
            }

            mGUI::RenderGUI();
            skybox.Draw();
            ss->setFloat("ex", ex);
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
namespace glx0224
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
        Shader* ss = GU_NORAML_SHADER;
        
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