#pragma once

#include <defines.h>

#include <spdlog/spdlog.h>


namespace OranGE {

namespace Log
{
    inline std::shared_ptr<spdlog::logger> s_Logger;

    void Init();

    void SetLevel(spdlog::level::level_enum level);

    void Shutdown();
}

}


#define LOG_TRACE(...)    ::OranGE::Log::s_Logger->trace(__VA_ARGS__)
#define LOG_INFO(...)     ::OranGE::Log::s_Logger->info(__VA_ARGS__)
#define LOG_WARN(...)     ::OranGE::Log::s_Logger->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::OranGE::Log::s_Logger->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::OranGE::Log::s_Logger->critical(__VA_ARGS__)
