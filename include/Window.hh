//
// Created by kate on 10/4/23.
//

#ifndef EVENT_SYSTEM_WINDOW_HH
#define EVENT_SYSTEM_WINDOW_HH

#include <atomic>
#include <string>

#include <Types.hh>

namespace Mikoto {
    struct WindowSpec {
        Int32_T Width{};
        Int32_T Height{};
        std::string Title{};
    };

    class Window {
    public:
        explicit Window(const WindowSpec& spec);

        MKT_NODISCARD auto GetWidth() const -> Int32_T { return m_Spec.Width; }
        MKT_NODISCARD auto GetHeight() const -> Int32_T { return m_Spec.Height; }
        MKT_NODISCARD auto GetTitle() const -> const std::string& { return m_Spec.Title; }

        auto SetWidth(Int32_T value) -> void { m_Spec.Width = value; }
        auto SetHeight(Int32_T value) -> void { m_Spec.Height = value; }
        auto SetTitle(std::string_view value) -> void { m_Spec.Title = value; }

    private:
        static inline Int32_T s_ActiveWindows{};
        static inline bool s_GLFWInitSuccess{};

        WindowSpec m_Spec{};
    };
}


#endif //EVENT_SYSTEM_WINDOW_HH
