//
// Created by kate on 10/4/23.
//

#ifndef EVENT_SYSTEM_WINDOW_HH
#define EVENT_SYSTEM_WINDOW_HH

#include <atomic>
#include <string>

#include <GLFW/glfw3.h>

#include <Types.hh>

namespace Mikoto {
    struct WindowSpec {
        Int32_T Width{};
        Int32_T Height{};
        std::string Title{};
        bool Resize{};
    };

    class Window {
    public:
        explicit Window(const WindowSpec& spec);

        MKT_NODISCARD auto GetWidth() const -> Int32_T { return m_Width; }
        MKT_NODISCARD auto GetHeight() const -> Int32_T { return m_Height; }
        MKT_NODISCARD auto GetTitle() const -> const std::string& { return m_Title; }

        auto SetWidth(Int32_T value) -> void { m_Width = value; }
        auto SetHeight(Int32_T value) -> void { m_Height = value; }
        auto SetTitle(std::string_view value) -> void { m_Title = value; }

        MKT_NODISCARD auto IsResizable() const -> bool { return m_Resizeable; }
        auto AllowResizing(bool value) -> void;

        auto PollEvents() -> void;

        ~Window();

    private:
        auto InstallCallbacks() -> void;
        auto SpawnOnCenter() const -> void;

        struct GLFWWindowCreateSpec {
            Int32_T Width{};
            Int32_T Height{};
            std::string_view Title{};
        };

        static auto InitGLFW() -> void;
        static auto DestroyGLFWWindow(GLFWwindow* window) -> void;
        static auto CreateGLFWWindow(const GLFWWindowCreateSpec& spec) -> GLFWwindow*;

    private:
        static inline Int32_T s_ActiveWindows{};
        static inline bool s_GLFWInitSuccess{};

        bool m_WindowCreateSuccess{};

        GLFWwindow* m_Window{};

        Int32_T m_Width{};
        Int32_T m_Height{};

        std::string m_Title{};

        bool m_Resizeable{};
    };
}


#endif //EVENT_SYSTEM_WINDOW_HH
