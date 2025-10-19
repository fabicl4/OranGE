#include "gl_program.h"

#include <iostream>
#include <stdexcept>

#include "../utils/file.h"

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
int checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    return success;
}

GLProgram GLProgram::createFromFile (const std::string& vertexPath,  const std::string& fragmentPath ) {
    std::string vertexSource;
    std::string fragmentSource;
    try {
        vertexSource = utils::loadFileToString(vertexPath);
        fragmentSource = utils::loadFileToString(fragmentPath);
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    GLuint vertex, fragment;

    // Compile vertex shader
    const char* src = vertexSource.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &src, NULL);
    glCompileShader(vertex);

    

    if (!checkCompileErrors(vertex, "VERTEX"))
    {
        throw std::runtime_error("Vertex shader failed to compile");
    }

    // Compile fragment shader
    src = fragmentSource.c_str();
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &src, NULL);
    glCompileShader(fragment);

    if (!checkCompileErrors(fragment, "FRAGMENT"))
    {
        throw std::runtime_error("Fragment shader failed to compile");
    }

    // shader Program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    if (!checkCompileErrors(program, "PROGRAM"))
    {
        throw std::runtime_error("Program failed to link");
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return GLProgram(program);
}

GLProgram::GLProgram(GLuint handle) {
    m_handle = handle;
}