#include "Shader.h"

#include <render/Device.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace OranGE {

Handle<Shader> ShaderManager::CreateShaderFromSource(const char* vertexSrc, const char* fragmentSrc)
{
    u32 gpu_id = m_Device->CreateShader(vertexSrc, fragmentSrc); // TODO: implement shader creation from source

    LOG_TRACE("[ShaderManager::CreateShaderFromSource] Created shader with GPU ID {}", gpu_id);

    Shader shader;
    shader.id = gpu_id;

    return CreateHandle(shader); 
}

Handle<Shader> ShaderManager::CreateShaderFromFiles(const char* vertexPath, const char* fragmentPath) {   
    // TODO: Update this to be more efficient and use PhysFS
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    return CreateShaderFromSource(vertexCode.c_str(), fragmentCode.c_str());
}

}