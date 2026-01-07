#include <platform.h>
#include <renderer.h>

namespace platform = core::platform;
namespace renderer = core::renderer;

i32 main()
{
    if (!platform::init("testbed", 800, 600))
        return -1;

    platform::push_input_handler([](platform::PlatformInputMessage message) {
        if (message.action == GLFW_PRESS)
            spdlog::info("what");
    });

    renderer::init();

    while (!platform::window_should_close()) {
        platform::pump_messages();
    }

    platform::deinit();
}
