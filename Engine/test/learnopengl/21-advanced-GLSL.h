#pragma once
#include "Engine.h"

#include <fstream>

// gl_PointSize测试
namespace glx0211
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_PROGRAM_POINT_SIZE);

        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();
        
        Drawable *drawable = (new Drawable())->SetDrawTypes(GL_POINTS)->SetVertexLayout(VertexNormallayout)->SetVertexNum(4)->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l1/"))->SetShader(GET_SHADER_PATH("/21/l1/ObjectVertex.vert"), GET_SHADER_PATH("/21/l1/ObjectFragment.frag"))->SetModel(glm::mat4(1));

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            // input
            // -----
            window->processInput();

            // render
            // ------
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }
        glDisable(GL_PROGRAM_POINT_SIZE);

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}
namespace glx0212
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable* drawable =    (new Drawable())\
                                ->SetDrawlayout(TextureDrawlayout)\
                                ->SetVertexLayout(VertexTexcoordlayout)\
                                ->SetVertexNum(36)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l2/"))\
                                ->SetShader(GET_SHADER_PATH("/EngineShaders/VertexTexcoord/ObjectVertex.vert"), GET_SHADER_PATH("/EngineShaders/VertexTexcoord/ObjectFragment.frag"))\
                                ->SetModel(glm::mat4(1))\
                                ->SetTextureId(GET_RESOURCE_PATH("imgs/woodPicture.jpeg"));
        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            // input
            // -----
            window->processInput();

            // render
            // ------
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            // cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// gl_FragCoord测试
namespace glx0213
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(VertexTexcoordlayout)\
                                ->SetVertexNum(36)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l2/"))\
                                ->SetShader(GET_SHADER_PATH("/21/l2/ObjectVertex.vert"), GET_SHADER_PATH("/21/l2/ObjectFragment.frag"))\
                                ->SetModel(glm::mat4(1));
        
        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            // input
            // -----
            window->processInput();

            // render
            // ------
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            // cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// 多贴图测试
namespace glx0214
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(VertexTexcoordlayout)\
                                ->SetVertexNum(36)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l3/"))\
                                ->SetShader(GET_SHADER_PATH("/21/l3/ObjectVertex.vert"), GET_SHADER_PATH("/21/l3/ObjectFragment.frag"))\
                                ->SetModel(glm::mat4(1))\
                                ->SetTextureId(GET_RESOURCE_PATH("imgs/woodPicture.jpeg"), "frontTexture")\
                                ->SetTextureId(GET_RESOURCE_PATH("imgs/container2.png"), "backTexture");
        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

        mGUI::Init();
        // render loop
        // -----------
        while (!window->WindowShouldClose())
        {
            window->UpdateDeltaTime();
            // input
            // -----
            window->processInput();

            // render
            // ------
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            // cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// gl_FrontFacing测试
namespace glx0215
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(VertexTexcoordlayout)\
                                ->SetVertexNum(36)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l3/"))\
                                ->SetShader(GET_SHADER_PATH("/21/l4/ObjectVertex.vert"), GET_SHADER_PATH("/21/l4/ObjectFragment.frag"))\
                                ->SetModel(glm::mat4(1))\
                                ->SetTextureId(GET_RESOURCE_PATH("imgs/woodPicture.jpeg"), "texture1");
        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

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
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            // cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}

// 接口块
namespace glx0216
{
   
    int main()
    {
        Window *window = Window::getWindow();
        CameraInstance *camera = CameraInstance::GetCamera();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        Drawable* drawable =    (new Drawable())\
                                ->SetVertexLayout(VertexTexcoordlayout)\
                                ->SetVertexNum(36)\
                                ->SetVertexFromData(GET_RESOURCE_PATH("/data/21/l3/"))\
                                ->SetShader(GET_SHADER_PATH("/21/l5/ObjectVertex.vert"), GET_SHADER_PATH("/21/l5/ObjectFragment.frag"))\
                                ->SetModel(glm::mat4(1))\
                                ->SetTextureId(GET_RESOURCE_PATH("imgs/woodPicture.jpeg"), "texture1");
        Drawable *cube = new Cube();
        Drawable *mmodel = new mModel();

        Plane plane;
        SkyBox skybox;
        FrameBufferObject fbo;

        Object *obj = new Object(glm::vec3(1, 1, 1));

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
            // fbo.SetFrameBuffer();
            window->Clear();

            mGUI::NewFrame();
            {
                ImGui::Begin("myGUI");
                ImGui::InputFloat3("Objet position", (float *)&(obj->Position));
                ImGui::End();
            }

            mGUI::RenderGUI();

            skybox.Draw();
            mmodel->Draw();
            drawable->Draw();
            // cubes
            // cube->Draw();
            // cube->DrawObject(obj);

            // floor
            plane.Draw();

            // fbo.SetMainFrameBuffer();
            // fbo.Draw();

            mGUI::DrawRenderData();
            window->SwapBufferAndPollEvents();
        }

        delete obj;
        delete cube;
        delete mmodel;
        delete drawable;
        mGUI::DestroyGUI();
        Window::DestoryWindow();
        CameraInstance::DestoryCamera();
        return 0;
    }

}