#pragma once

#include "defines.h"

namespace OranGE::gfx {

// The Context struct holds the current state of the graphics pipeline (e.g. blend state, depth test state, etc.)
// This allows the Device to track the current state and avoid redundant state changes, which can improve performance.
struct Context
{
    struct {
        bool blendEnabled;
        u32 blendSrcRGB;
        u32 blendDstRGB;
        u32 blendSrcAlpha;
        u32 blendDstAlpha;
        float blendColor[4];
    } blendState;
    
    // Depth-Stencil
    struct {
       bool depthTestEnabled;
        bool depthWriteEnabled;
        u32 depthCompareOp;  // GL_LESS, GL_LEQUAL, etc
        bool stencilTestEnabled;
        // ... stencil ops front/back
    } depthStencilState;;
    
    // Rasterizations state
    struct {
        bool cullEnabled;
        u32 cullFace;      // GL_BACK, GL_FRONT
        u32 frontFace;     // GL_CCW, GL_CW
        u32 polygonMode;   // GL_FILL, GL_LINE, GL_POINT
        float lineWidth;
        float pointSize;
        bool depthClampEnabled;
        bool rasterizerDiscard;
    } rasterState;

    // Shaders and pipelines
    // Program bindings
    u32 activeProgram;

    // Vertex input
    u32 activeVAO;

    // Framebuffer
    struct {
        u32 drawFramebuffer;
        u32 readFramebuffer;
        u32 drawBuffer;       // GL_COLOR_ATTACHMENT0, etc
    } framebufferState;

    u32 viewport[4];
    bool scissorEnabled;
    u32 scissor[4];
};

// Vulkan Pipeline-like state object that encapsulates all the relevant state for a draw call
struct PipelineState
{
    u32 shaderProgram;

    u32 activeVAO;

    struct {
        u32 slot;
        u32 textureId;
    } textures[16]; // support up to 16 texture slots

    struct {
        u32 drawFramebuffer;
        u32 readFramebuffer;
        u32 drawBuffer;       // GL_COLOR_ATTACHMENT0, etc
    } framebufferState;
    
};


};