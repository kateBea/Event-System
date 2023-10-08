//
// Created by kate on 10/4/23.
//

#include <GLFW/glfw3.h>

#include <Logger.hh>
#include <CoreEvents.hh>
#include <EventManager.hh>
#include <Window.hh>

namespace Mikoto {

    Window::Window(const WindowSpec& spec) {
        MKT_CORE_LOGGER_INFO("Main Window initialization");
        m_Width = spec.Width;
        m_Height = spec.Height;
        m_Title = spec.Title;

        AllowResizing(spec.Resize);

        // Initialize GLFW Library
        InitGLFW();

        // Allow resizing
        if (IsResizable()) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        }
        else {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }

        GLFWWindowCreateSpec param{};
        param.Width = GetWidth();
        param.Height = GetHeight();
        param.Title = GetTitle();

        m_Window = CreateGLFWWindow(param);

        m_WindowCreateSuccess = m_Window != nullptr;
        MKT_ASSERT(m_WindowCreateSuccess, "Failed to create the Window GLFW");
        MKT_CORE_LOGGER_INFO("Created GLFW Window with name '{}'", GetTitle());
        MKT_CORE_LOGGER_INFO("Created GLFW Window with dim [{}, {}]", GetWidth(), GetHeight());

        InstallCallbacks();
    }

    auto Window::AllowResizing(bool value) -> void {
        m_Resizeable = value;

        if (m_Resizeable) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        }
        else {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }
    }

    auto Window::InstallCallbacks() -> void {
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetWindowSizeCallback(m_Window,
                                  [](GLFWwindow* window, Int32_T width, Int32_T height) -> void {
                                      Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
                                      data->SetWidth(width);
                                      data->SetHeight(height);

                                      EventManager::Trigger<WindowResizedEvent>(width, height);
                                  }
        );

        glfwSetWindowCloseCallback(m_Window,
                                   [](GLFWwindow* window) {
                                       const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };

                                       EventManager::Trigger<WindowCloseEvent>();
                                   }
        );

        glfwSetKeyCallback(m_Window,
                           [](GLFWwindow* window, Int32_T key, [[maybe_unused]] Int32_T  scancode, Int32_T action, Int32_T mods) -> void {
                               const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };

                               switch (action) {
                                   case GLFW_PRESS: {
                                       EventManager::Trigger<KeyPressedEvent>(key, false, mods);
                                       break;
                                   }
                                   case GLFW_RELEASE: {
                                       EventManager::Trigger<KeyReleasedEvent>(key);
                                       break;
                                   }
                                   case GLFW_REPEAT: {
                                       EventManager::Trigger<KeyPressedEvent>(key, true, mods);
                                       break;
                                   }
                                   default: {
                                       MKT_CORE_LOGGER_WARN("Unknown Key action for key callback");
                                       break;
                                   }
                               }
                           }
        );

        glfwSetMouseButtonCallback(m_Window,
                                   [](GLFWwindow* window, Int32_T button, Int32_T action, Int32_T mods) -> void {
                                       const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };

                                       switch (action) {
                                           case GLFW_PRESS: {
                                               MouseButtonPressedEvent mousePressed{ button, mods };
                                               break;
                                           }
                                           case GLFW_RELEASE: {
                                               MouseButtonReleasedEvent mouseReleased{ button };
                                               break;
                                           }
                                           default:
                                               MKT_CORE_LOGGER_WARN("Unknown GLFW_ value for glfwSetMouseButtonCallback");
                                               break;
                                       }
                                   }
        );

        glfwSetScrollCallback(m_Window,
                              [](GLFWwindow* window, double xOffset, double yOffset) -> void {
                                  const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
                                  MouseScrollEvent msc{ xOffset, yOffset };
                              }
        );

        glfwSetCursorPosCallback(m_Window,
                                 [](GLFWwindow* window, double x, double y) -> void {
                                     const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
                                     EventManager::Trigger<MouseMovedEvent>(x, y);
                                 }
        );

        glfwSetCharCallback(m_Window,
                            [](GLFWwindow* window, UInt32_T codePoint) -> void {
                                const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
                                KeyCharEvent kce{ codePoint };
                            }
        );

        // This function will be called when this window gets focus
        glfwSetWindowFocusCallback(m_Window,
                                   [](GLFWwindow* window, Int32_T focus) -> void {
                                       const Window* data{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
                                       if (focus == GLFW_TRUE) {

                                       }
                                   });
    }

    Window::~Window() {
        MKT_CORE_LOGGER_INFO("Shutting down GLFW Window with name '{}'", GetTitle());
        MKT_CORE_LOGGER_INFO("GLFW Window dimensions are [{}, {}]", GetWidth(), GetHeight());

        DestroyGLFWWindow(m_Window);
    }

    auto Window::DestroyGLFWWindow(GLFWwindow* window) -> void {
        // Everytime we shut down a GLFW window, we decrease the number
        // of active windows, the last GLFW window to be shutdown calls glfwTerminate()
        glfwDestroyWindow(window);
        // TODO: thread safety
        s_ActiveWindows -= 1;

        if (s_ActiveWindows == 0) {
            glfwTerminate();
        }
    }

    auto Window::CreateGLFWWindow(const GLFWWindowCreateSpec &spec) -> GLFWwindow* {
        // TODO: thread safety?

        GLFWwindow* window{ nullptr };
        window = glfwCreateWindow(spec.Width, spec.Height, spec.Title.data(), nullptr, nullptr);
        s_ActiveWindows += 1;

        return window;
    }

    auto Window::PollEvents() -> void {
        glfwPollEvents();
    }

    auto Window::InitGLFW() -> void {
        if (!s_GLFWInitSuccess) {
            auto ret{ glfwInit() };
            MKT_ASSERT(ret == GLFW_TRUE, "Failed to initialized the GLFW library");

            s_GLFWInitSuccess = true;
            glfwSetErrorCallback([](std::int32_t errCode, const char* desc) -> void {
                                     MKT_CORE_LOGGER_ERROR("GLFW error code: {} Description: {}", errCode, desc);
                                 }
            );
        }
    }
}
