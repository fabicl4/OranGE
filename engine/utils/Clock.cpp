#include "Clock.h"

#include <chrono>

Clock::Clock()
    : m_startTime(0.0)
    , m_elapsed(0.0)
    , m_stopped(true)
{
}

static f64 getCurrentSeconds()
{
    using clock = std::chrono::high_resolution_clock;
    auto now      = clock::now();
    auto epoch    = now.time_since_epoch();
    return std::chrono::duration<f64>(epoch).count();
}

f64 Clock::GetStartTime() const noexcept
{
    return m_startTime;
}

f64 Clock::GetElapsed() const noexcept
{
    return m_elapsed;
}

void Clock::Update()
{
    if (m_stopped)
        return;

    f64 now = getCurrentSeconds();
    m_elapsed = now - m_startTime;
}

void Clock::Start()
{
    m_startTime = getCurrentSeconds();
    m_elapsed = 0.0;
    m_stopped = FALSE;
}

void Clock::Stop()
{
    if (!m_stopped)
    {
        Update();
        m_stopped = TRUE;
    }
}
