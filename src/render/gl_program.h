#pragma once

#include <string>

#include "gl_resource.h"

class GLProgram : public GLResource<GLProgram> {
private:
    GLProgram() = delete;

    explicit GLProgram(GLuint handle);

public:
    // Factory pattern
    static GLProgram createFromFile (
        const std::string& vertexPath, 
        const std::string& fragmentPath );
    
    void use() const noexcept { glUseProgram(m_handle); }

    void destroy() noexcept { glDeleteProgram(m_handle); }
};