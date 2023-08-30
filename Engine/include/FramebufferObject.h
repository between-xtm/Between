#pragma once
#include "Render.h"

class FramebufferObject : public Render
{
public:
    FramebufferObject()
    {
        Init();
    }

    void Init();
    void Draw(Shader *specialShader = nullptr);
    void SetFrameBuffer();
    void SetMainFrameBuffer();
    
private:
    unsigned int framebuffer, rbo, textureColorBufferMultiSampled, intermediateFBO, screenTexture;
};
