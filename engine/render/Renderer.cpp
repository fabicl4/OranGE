#include "Renderer.h"

#include <core/Log.h>

#include "Device.h"

namespace OranGE::gfx {

Renderer::Renderer(Device* device, const Viewport& viewport)
    : m_Device(device), m_Viewport(viewport)
{
    LOG_TRACE("[Renderer]Created renderer with viewport {}x{}", viewport.width, viewport.height);

    m_Device->SetViewport(viewport.width, viewport.height);

    m_Stats.frameTime = 0.0f;
    m_Stats.drawCalls = 0;
    m_Stats.triangleCount = 0;

    // Create default resources (e.g. white texture, default shader)

    // Request command buffers from the device.
}

void Renderer::BeginFrame()
{
    m_Stats.frameTime = 0.0f;
    m_Stats.drawCalls = 0;
    m_Stats.triangleCount = 0;

    m_Device->Clear(0.1f, 0.1f, 0.1f, 1.0f); // clear to dark gray
}

void Renderer::EndFrame()
{
    // Flush command buffers to the GPU
    // Present the frame (swap buffers, etc.)
    // Update frame stats (e.g. calculate frame time)
}

void Renderer::Submit(const Mesh& mesh, const Shader& shader)
{
    m_Device->BindShader(shader.id);
    m_Device->BindVertexArray(mesh.vertexArray);
    //m_Device->BindBuffer(mesh.indexBuffer);

    m_Device->Draw(0, mesh.vertexCount);

    //m_Stats.drawCalls++;
    //m_Stats.triangleCount += mesh.vertexCount / 3;
}


void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    m_Device->SetViewport(width, height);
}

void Renderer::OnWindowResize(int width, int height)
{
    OnWindowResize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

void Renderer::OnWindowFocus()
{
    LOG_TRACE("[Renderer] Window focused");
}

void Renderer::OnWindowLostFocus()
{
    LOG_TRACE("[Renderer] Window lost focus");
}

void Renderer::OnWindowMaximize()
{
    LOG_TRACE("[Renderer] Window maximized");
}



};