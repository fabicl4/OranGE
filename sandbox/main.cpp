#include <iostream>

#include <OranGE-Core.h>

class TestApp : public OranGE::Application {
public:
    TestApp(const OranGE::ApplicationConfig& config) 
        : Application(config) {};

protected:
    virtual bool OnCreate() override {
        LOG_TRACE("[TestApp::OnCreate] Hello World!");

        // Load default shader
        const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        m_Shader = m_ShaderManager->CreateShaderFromSource(vertexShaderSource, fragmentShaderSource);

        // Define a simple triangle mesh
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left  
            0.5f, -0.5f, 0.0f, // right 
            0.0f,  0.5f, 0.0f  // top   
        };

        int vertexCount = 3;

        OranGE::VertexLayout layout(
        {
            {
                "vertices", //name
                0,          //type
                3 * sizeof(float), //size
                0,          //offset
                false, // isNormalized
            },
        });

        OranGE::MeshData meshData = {
            vertices,
            vertexCount,
            layout
        };

        m_Mesh = m_MeshManager->CreateMesh(meshData);

        LOG_TRACE("[TestApp::OnCreate] Shader {} Generation {}; Mesh {} Generation {}", 
            m_Shader.GetId(), m_Shader.GetGeneration(), m_Mesh.GetId(), m_Mesh.GetGeneration());

        if (!m_Shader.IsValid()) {
            LOG_ERROR("[TestApp::OnCreate] Failed to create shader");
            return false;
        }

        if (!m_Mesh.IsValid()) {
            LOG_ERROR("[TestApp::OnCreate] Failed to create mesh");
            return false;
        }

        LOG_TRACE("[TestApp::OnCreate] Resources created!");

        return true;
    };

    virtual bool OnDestroy() override{
        LOG_TRACE("[TestApp::OnDestroy] Goodbye World!");

        return true;
    };

    virtual bool OnUpdate(f64 ts) override {
        // ts is delta time since last frame in seconds
        //LOG_TRACE("[TestApp::OnUpdate] delta={} run={}", ts, GetRunTime());
        return true;
    };

    virtual bool OnRender() override 
    {
        // Get resources from managers using handles
        OranGE::Shader shader = m_ShaderManager->GetResource(m_Shader);
        OranGE::Mesh mesh = m_MeshManager->GetResource(m_Mesh);

        m_Renderer->Submit(mesh, shader);

        return true;
    };

    //virtual void OnEvent() override {};

private:
    OranGE::ShaderHandle m_Shader;
    OranGE::MeshHandle m_Mesh;

};

int main() 
{
    OranGE::ApplicationConfig config;

    config.title = std::string("Test App");
    config.width = 800;
    config.height = 600;

    TestApp* app = new TestApp(config);

    std::cout << "Create test app" << std::endl;

    app->Run();

    std::cout << "Close app";

    return 0;

}