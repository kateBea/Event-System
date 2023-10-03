//
// Created by kate on 10/4/23.
//

#ifndef EVENT_SYSTEM_APPLICATION_HH
#define EVENT_SYSTEM_APPLICATION_HH

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
        State m_State{ State::RUNNING };
    };
}


#endif //EVENT_SYSTEM_APPLICATION_HH
