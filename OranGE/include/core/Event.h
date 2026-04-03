#pragma once

#include "types.h"

#include <string>

// Event system inspired by Hazel's implementation:
// https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Events/Event.h

namespace OranGE {
    
enum class EventType
{
    None = 0,
    WindowResize,
    WindowClose,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved
};

// Base event class
class Event {
public:
    Event() = default;
    virtual ~Event() = default;

    // Add common event functionality here (e.g., event type, category, etc.)

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string ToString() const { return GetName(); }
};

class EventDispatcher {
public:
    EventDispatcher(Event& event)
        : m_Event(event) {}

    template<typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }
private:    
    Event& m_Event;
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height) {}

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    static EventType GetStaticType() { return EventType::WindowResize; }
    virtual EventType GetEventType() const override { return GetStaticType(); }
    virtual const char* GetName() const override { return "WindowResizeEvent"; }

private:
    uint32_t m_Width;
    uint32_t m_Height;
};

};