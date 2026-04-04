#include <core/Log.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace OranGE;

namespace OranGE
{
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::Initialize() {

        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_Logger = spdlog::stdout_color_mt("OranGE");
        s_Logger->set_level(spdlog::level::trace);
    }

    void Log::SetLevel(spdlog::level::level_enum level) {
        s_Logger->set_level(level);
    }

    void Log::Shutdown() {
        spdlog::shutdown();
    }
}
