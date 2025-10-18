#include "gl_resource.h"

// RAII Texture 
class GLTexture : public GLResource<GLTexture> {
public:
    GLTexture() { glGenTextures(1, &handle_); }

    void destroy() noexcept { glDeleteTextures(1, &handle_); }

protected:
    // texture metadata
    int width, height, numColor;
};