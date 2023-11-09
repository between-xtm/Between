#include "Engine.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Windows.h>
#include <commdlg.h>
#include <gdiplus.h>
// #pragma comment(lib, "gdiplus.lib")

std::string originImgae("");
std::string lutImgae("");
bool originChanged = false;
bool lutChanged = false;
GLuint texture1, texture2;
bool snap = false;

void loadTexture(std::string pth, bool isOrigin)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    if(isOrigin)
    {
        stbi_set_flip_vertically_on_load(true);
    } else
    {
        stbi_set_flip_vertically_on_load(false);
    }
    if(isOrigin)
    {
        // glDeleteTextures(1, &texture1);
        glGenTextures(1, &texture1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
    } else
    {
        // glDeleteTextures(1, &texture2);
        glGenTextures(1, &texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
    }
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载纹理图片
    int width, height, nrChannels;
    unsigned char *data = stbi_load(pth.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if(nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);

}

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
    if (ImGui::Button("button3"))
    {
        snap = true;
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
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // right
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,    // top
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };
    
    Render* render = new Render();
    render->SetVertex(vertices, VertexLayout::VertexTexcoordlayout, sizeof(vertices));
    std::cout << getFilePath() << std::endl;
    render->SetShader("E:/Project/Between/test/vertex.vert", "E:/Project/Between/test/fragment.frag");
    // loadTexture("E:/Project/Between/test/origin.png", true);
    // loadTexture("E:/Project/Between/test/lut.png", false);
    // render->GetShader()->use();
    // render->GetShader()->setInt("texture1", 0);
    // render->GetShader()->setInt("texture2", 1);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture1);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, texture2);
    glfwSetInputMode(window->getGlfwWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    
    while (!glfwWindowShouldClose(window->getGlfwWindow()))
    {
        // glViewport(0,0,256,16);
        window->processInput();
        window->Clear(0,0,0,1);
        auto camera = CameraInstance::getCamera();
        camera->updateUniform(true);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        if(originChanged)
        {
            // render->DeleteAllTextures();
            loadTexture(originImgae, true);
            render->GetShader()->use();
            render->GetShader()->setInt("texture1", 0);
            
            originChanged = false;
        }
        if(lutChanged)
        {
            // render->DeleteAllTextures();
            loadTexture(lutImgae, false);
            render->GetShader()->use();
            render->GetShader()->setInt("texture2", 1);
            lutChanged = false;
        }
        render->Draw();
     
        // 渲染ImGui界面
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 绘制ImGui界面
        renderUI();


        
        // 渲染ImGui界面到OpenGL上下文
        ImGui::Render();
        if(snap == true)
        {
            
            snap = false;
            unsigned char* pixels = new unsigned char[800 * 600 * 4];

            // 使用glReadPixels函数读取纹理数据
            glReadPixels(0, 0, 800, 600, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            // 将读取到的纹理数据保存为PNG图片
            // if (stbi_write_png("saved_texture.png", width, height, channels, pixels, width * channels) == 0) {
            //     // 处理保存纹理失败的情况
            // } else {
            //     // 处理保存纹理成功的情况
            // }
            printf("%c\n", pixels[1]);
            // 记得释放内存
            delete[] pixels;
        }
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->SwapBufferAndPollEvents();
    }

    // 清理ImGui资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

        return 0;
    }
