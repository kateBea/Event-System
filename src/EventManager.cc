//
// Created by kate on 10/7/23.
//

#include <utility>
#include <algorithm>

#include <Types.hh>
#include <EventManager.hh>

namespace Mikoto::EventManager {
    auto Unsubscribe(UInt64_T subId, EventType type) -> void {
        if (s_Subscribers.contains(subId)) {

        }
    }

    auto Unsubscribe(UInt64_T subId, EventCategory category) -> void {
        if (s_Subscribers.contains(subId)) {

        }
    }

    auto ProcessEvents() -> void {
        // Traverse event queue
        auto begin{ s_EventQueue.begin() };
        for ( ; begin != s_EventQueue.end(); ++begin) {
            auto& eventPtr{ *begin };

            for (auto& [subId, listOfHandlers] : s_Subscribers) {
                const auto handlerWrapper{ std::find_if(listOfHandlers.begin(),
                                              listOfHandlers.end(),
                                              [&](const EventHandlerWrapper& a) -> bool { return eventPtr->IsInCategory(a.GetCategory()) && a.GetType() == eventPtr->GetType(); }) };

                if (handlerWrapper != listOfHandlers.end()) { handlerWrapper->GetHandler()(*eventPtr); }
            }
        }

        s_EventQueue.clear();
    }

    auto Shutdown() -> void {

    }
}
