//
// Created by kate on 10/4/23.
//

#ifndef EVENT_SYSTEM_APPLICATION_HH
#define EVENT_SYSTEM_APPLICATION_HH

#include <Window.hh>

namespace Mikoto {
    class Application {
    public:
        auto Init() -> void;
        auto Run() -> void;
        auto Shutdown() -> void;

    private:
        enum class State {
            RUNNING,
            STOPPED,
        };

    private:
        // UUID
        UInt64_T uuid{ 54 };

        // Main application window
        std::unique_ptr<Window> m_Window{};

        // Represents application current state
        State m_State{ State::RUNNING };
    };
}


#endif //EVENT_SYSTEM_APPLICATION_HH
