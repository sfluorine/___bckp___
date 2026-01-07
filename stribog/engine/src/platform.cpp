#include "platform.h"

#include <spdlog/spdlog.h>

#include <memory_resource>

namespace core {

namespace platform {

static GLFWwindow* s_window { nullptr };

static std::pmr::synchronized_pool_resource s_arena {};
static std::pmr::vector<PlatformInputHandler> s_input_handlers { &s_arena };
static std::pmr::vector<PlatformWindowHandler> s_window_handlers { &s_arena };

bool STRIBOG_API init(char const* app_name, u32 width, u32 height)
{
    auto error_callback = [](i32 code, char const* description) {
        spdlog::error("[PLATFORM ERROR]: {}: {}", code, description);
    };

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    s_window = glfwCreateWindow(
        width, height,
        app_name,
        nullptr, nullptr);

    if (!s_window)
        return false;

    glfwSetKeyCallback(s_window, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
        for (auto handler : s_input_handlers)
            handler(PlatformInputMessage { action, key, mods });
    });

    glfwSetFramebufferSizeCallback(s_window, [](GLFWwindow* window, i32 width, i32 height) {
        PlatformWindowMessage message {};
        message.type = PlatformWindowMessage::FramebufferResize;
        message.resize = { static_cast<u32>(width), static_cast<u32>(height) };

        for (auto handler : s_window_handlers)
            handler(message);
    });

    return true;
}

void STRIBOG_API deinit()
{
    glfwDestroyWindow(s_window);
    glfwTerminate();
}

bool STRIBOG_API window_should_close()
{
    return glfwWindowShouldClose(s_window);
}

void STRIBOG_API pump_messages()
{
    glfwPollEvents();
}

void STRIBOG_API push_input_handler(PlatformInputHandler handler)
{
    s_input_handlers.push_back(handler);
}

void STRIBOG_API push_window_handler(PlatformWindowHandler handler)
{
    s_window_handlers.push_back(handler);
}

VkSurfaceKHR STRIBOG_API create_surface(VkInstance instance)
{
    VkSurfaceKHR surface {};

#if defined(STRIBOG_WINDOWS)
    // TODO: handle surface creation in windows.
#elif defined(STRIBOG_LINUX)
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) {
        VkWaylandSurfaceCreateInfoKHR info {};
        info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
        info.surface = glfwGetWaylandWindow(s_window);
        info.display = glfwGetWaylandDisplay();
        VK_CHECK(vkCreateWaylandSurfaceKHR(instance, &info, nullptr, &surface));
    } else {
        VkXlibSurfaceCreateInfoKHR info {};
        info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        info.window = glfwGetX11Window(s_window);
        info.dpy = glfwGetX11Display();
        VK_CHECK(vkCreateXlibSurfaceKHR(instance, &info, nullptr, &surface));
    }
#endif
    return surface;
}
}
}
