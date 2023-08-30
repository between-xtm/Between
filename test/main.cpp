#include "Engine.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>

#include <Windows.h>
#include <commdlg.h>


std::string originImgae("");
std::string lutImgae("");
bool originChanged = false;
bool lutChanged = false;

std::string openFileSelectionDialog()
{
    OPENFILENAME ofn;
    CHAR szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All Files\0*.*\0"; // 可以根据需要设置文件过滤器
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return ofn.lpstrFile;
    }
    else
    {
        return ""; // 如果用户取消了选择，则返回空字符串
    }
}

void renderUI()
{
    ImGui::Begin("title");
    ImGui::SetWindowSize(ImVec2(300, 100));
    if (ImGui::Button("originTexture"))
    {
        originImgae = openFileSelectionDialog();
        originChanged = true;
    }
    if (ImGui::Button("button2"))
    {
        lutImgae = openFileSelectionDialog();
        lutChanged = true;
    }

    ImGui::End();
}
 int main()

    {

    Window* window = Window::getWindow();
    std::string a;
    

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window->getGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };
    
    Render* render = new Render();
    render->SetVertex(vertices, VertexLayout::Vertexlayout, sizeof(vertices));
    std::cout << getFilePath() << std::endl;
    render->SetShader("..\\..\\Engine\\resource\\shaders\\3\\l1\\vertex.vert", "..\\..\\Engine\\resource\\shaders\\3\\l1\\fragment.frag");

    glfwSetInputMode(window->getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    while (!glfwWindowShouldClose(window->getGlfwWindow()))
    {

        window->processInput();
        window->Clear(0,0,0,1);

        // 渲染ImGui界面
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 绘制ImGui界面
        renderUI();


        
        // 渲染ImGui界面到OpenGL上下文
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(originChanged || lutChanged)
        {
            
        }
        render->Draw();
        window->SwapBufferAndPollEvents();
    }

    // 清理ImGui资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    // if(ImGui::Button("select Image"))
    // {
    //     a = openFileSelectionDialog();
    // }
    // ImGui::Render();
    std::cout<<a<<std::endl;


    
        //
        // Window* window = Window::getWindow();
        //
        // float vertices[] = {
        //     -0.5f, -0.5f, 0.0f, // left
        //     0.5f, -0.5f, 0.0f,  // right
        //     0.0f, 0.5f, 0.0f    // top
        // };
        //
        // Render* render = new Render();
        // render->SetVertex(vertices, VertexLayout::Vertexlayout, sizeof(vertices));
        // std::cout << getFilePath() << std::endl;
        // render->SetShader("..\\..\\Engine\\resource\\shaders\\3\\l1\\vertex.vert", "..\\..\\Engine\\resource\\shaders\\3\\l1\\fragment.frag");
        // // render loop
        // // -----------
        // while (!glfwWindowShouldClose(window->getGlfwWindow()))
        // {
        //
        //
        //     
        //
        //     // render
        //     // ------
        //     window->processInput();
        //     window->Clear(0,0,0,1);
        //     render->Draw();
        //     window->SwapBufferAndPollEvents();
        // }
        //
        //
        // // glfw: terminate, clearing all previously allocated GLFW resources.
        // // ------------------------------------------------------------------
        // glfwTerminate();
        return 0;
    }
