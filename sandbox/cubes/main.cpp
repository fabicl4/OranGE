#include <OranGE-Core.h>

// Spinning cube

#include "camera.h"
#include "transform.h"

class CubesApp : public OranGE::Application {
public:
    CubesApp(const OranGE::ApplicationConfig& config) 
        : Application(config) {

        };

    virtual bool OnCreate() override {
        m_Shader = m_ShaderManager->CreateShaderFromFiles("assets/shaders/cube.vs", "assets/shaders/cube.fs");

        if (!m_Shader.IsValid()) {
            LOG_ERROR("[CubesApp::OnCreate] Failed to load shader");
            return false;
        }

        // Call factory function.
        m_Mesh = m_MeshManager->CreateCube();

        if (!m_Mesh.IsValid()) {
            LOG_ERROR("[CubesApp::OnCreate] Failed to create mesh");
            return false;
        }

        m_Texture = m_TextureManager->LoadTextureFromFile("assets/textures/container.jng");
        if (!m_Texture.IsValid()) {
            LOG_ERROR("[CubesApp::OnCreate] Failed to load texture");
            return false;
        }

        // Create a uniform buffer to upload camera data!
    }

    virtual bool OnUpdate(f64 ts) override {
        // Update cube data
        // Update camera data
        return true;
    };

    virtual bool OnRender() override {
        // Submit draw call!
        OranGE::Shader shader = m_ShaderManager->GetResource(m_Shader);
        OranGE::Mesh mesh = m_MeshManager->GetResource(m_Mesh);
        OranGE::Texture texture = m_TextureManager->GetResource(m_Texture);

        // Uniform data and camera data

        m_Renderer->Submit(mesh, shader, texture);
    }

private:

    ShaderHandle m_Shader{};
    MeshHandle m_Mesh {};
    TextureHandle m_Texture {};

    /* Camera data */
    /* Cube data */

};

int main() 
{
    OranGE::ApplicationConfig config;

    config.title = std::string("Test App");
    config.width = 800;
    config.height = 600;

    CubesApp* app = new CubesApp(config);

    app->Run();


    return 0;

}