#include <glad/glad.h>

template <typename Derived, typename HandleType = GLuint>
class GLResource {
protected:
    HandleType m_handle;
public:
    GLResource() = default;
    
    // Non copyable
    GLResource(const GLResource&) = delete;

    // Move
    GLResource& operator=(GLResource&& other) noexcept : m_handle(other.m_handle) {
        other.m_handle = 0;
    }
        GLResource& operator=(GLResource&& other) noexcept {
        if (this != &other) {
            release();
            handle_ = other.m_handle;
            other.handle_ = 0;
        }
        return *this;
    }
    virtual ~GLResource() { release(); }

    HandleType handle() const noexcept { return m_handle; }

protected:
    // Derived class must implement release()
    void release() noexcept {
        if (m_handle) {
            static_cast<Derived*>(this)->destroy();
            handle_ = 0;
        }
    }
};