#pragma once

#include "types.h"

// Based of: http://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h

// This ignores all warnings raised inside External headers
#if defined(_WIN32)
    #pragma warning(push)
    #pragma warning(disable : 4996) // example for MSVC
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wall" // adjust as needed
#endif

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#if defined(_WIN32)
    #pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif

#include <memory>

namespace OranGE {


class Log {
public:
    static std::shared_ptr<spdlog::logger>& Get() {
        return s_Logger;
    }

    static void Initialize();
    static void SetLevel(spdlog::level::level_enum level);
    static void Shutdown();

private:
    static std::shared_ptr<spdlog::logger> s_Logger;

};

}

#define LOG_INITIALIZE() ::OranGE::Log::Init()
#define LOG_TRACE(...)    ::OranGE::Log::Get()->trace(__VA_ARGS__)
#define LOG_INFO(...)     ::OranGE::Log::Get()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::OranGE::Log::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::OranGE::Log::Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::OranGE::Log::Get()->critical(__VA_ARGS__)


// GLM types support

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}