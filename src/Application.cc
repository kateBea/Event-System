//
// Created by kate on 10/4/23.
//

#include <iostream>
#include <thread>

#include <Common.hh>

#include <Logger.hh>

#include <Event.hh>
#include <KeyEvents.hh>
#include <MouseEvents.hh>
#include <EventManager.hh>
#include <Application.hh>

namespace Mikoto {
    auto Application::Init() -> void {
        using namespace EventManager;

        EventManager::Subscribe(uuid,
            EventType::WINDOW_CLOSE_EVENT,
            [this](Event&) -> bool
            {
                m_State = State::STOPPED;
                MKT_CORE_LOGGER_INFO("Received Event close");
                return false;
            });

        EventManager::Subscribe(uuid,
            EventType::KEY_PRESSED_EVENT,
            [this](Event& event) -> bool
            {
                MKT_CORE_LOGGER_INFO("Pressed Key {}", static_cast<KeyPressedEvent&>(event).GetKeyCode());
                return false;
            });

        EventManager::Subscribe(uuid,
            EventType::MOUSE_MOVED_EVENT,
            [this](Event& event) -> bool
            {
                MKT_CORE_LOGGER_INFO("Mouse position Key [{},{}]", static_cast<MouseMovedEvent&>(event).GetPositionX(),
                                     static_cast<MouseMovedEvent&>(event).GetPositionY());
                return false;
            });

        WindowSpec spec{ 640, 480, "EventSystem", true };
        m_Window = std::make_unique<Window>(std::move(spec));
    }

    auto Application::Run() -> void {
        while(m_State == State::RUNNING) {
            m_Window->PollEvents();
            EventManager::ProcessEvents();
        }
    }

    auto Application::Shutdown() -> void {

    }
}