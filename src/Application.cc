//
// Created by kate on 10/4/23.
//

#include <iostream>
#include <Common.hh>
#include <Application.hh>

namespace Mikoto {
    auto Application::Init() -> void {

    }

    auto Application::Run() -> void {
        while(m_State == State::RUNNING) {
            // do stuff

            // TODO: do actual stuff
            int num{};
            MKT_COLOR_PRINT_FORMATTED(MKT_FMT_COLOR_CORAL, "Enter an integer: ");
            std::cin >> num;

            if (num) {
                m_State = State::STOPPED;
            }
        }
    }

    auto Application::Shutdown() -> void {

    }
}