#include "gl_resource.h"

// RAII Texture 
class GLTexture : public GLResource<GLTexture> {
public:
    GLTexture() { glGenTextures(1, &m_handle); }

    void destroy() noexcept { glDeleteTextures(1, &m_handle); }

protected:
    // texture metadata
    int width, height, numColor;
};