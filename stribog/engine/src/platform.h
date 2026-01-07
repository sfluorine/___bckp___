#pragma once

#include "defines.h"
#include "vulkan_interface.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace core {

namespace platform {

struct PlatformInputMessage {
    i32 action;
    i32 key;
    i32 mods;
};

struct PlatformWindowMessage {
    enum {
        FramebufferResize
    } type;

    union {
        struct {
            u32 width;
            u32 height;
        } resize;
    };
};

using PlatformInputHandler = void (*)(PlatformInputMessage);
using PlatformWindowHandler = void (*)(PlatformWindowMessage);

bool STRIBOG_API init(char const* app_name, u32 width, u32 height);

void STRIBOG_API deinit();

bool STRIBOG_API window_should_close();

void STRIBOG_API pump_messages();

void STRIBOG_API push_input_handler(PlatformInputHandler handler);

void STRIBOG_API push_window_handler(PlatformWindowHandler handler);

VkSurfaceKHR STRIBOG_API create_surface(VkInstance instance);

}

}
