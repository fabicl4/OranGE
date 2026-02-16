#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

using namespace OranGE;

namespace OranGE::Log
{
    void Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_Logger = spdlog::stdout_color_mt("OranGE");
        s_Logger->set_level(spdlog::level::trace);
    }

    void SetLevel(spdlog::level::level_enum level) {
        s_Logger->set_level(level);
    }

    void Shutdown() {
        spdlog::shutdown();
    }
}
