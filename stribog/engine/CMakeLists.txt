cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

project(engine_vulkan CXX)

if(WIN32)
  set(VOLK_STATIC_DEFINES
    VK_NO_PROTOTYPES
    VK_USE_PLATFORM_WIN32_KHR
    GLFW_INCLUDE_NONE)
elseif(UNIX AND NOT APPLE)
  set(VOLK_STATIC_DEFINES
    VK_NO_PROTOTYPES
    VK_USE_PLATFORM_WAYLAND_KHR
    VK_USE_PLATFORM_XLIB_KHR
    GLFW_INCLUDE_NONE)
endif()

add_subdirectory(vendor/volk)
add_subdirectory(vendor/vk-bootstrap)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)

add_library(
  engine_vulkan STATIC
  src/defines.h
  src/vulkan_interface.h
  src/platform.h
  src/platform.cpp
  src/renderer.h
  src/renderer.cpp
)

if(WIN32)
  target_compile_definitions(
    engine_vulkan PUBLIC
    STRIBOG_WINDOWS
  )
elseif(UNIX AND NOT APPLE)
  target_compile_definitions(
    engine_vulkan PUBLIC
    STRIBOG_LINUX
  )
endif()

target_include_directories(
  engine_vulkan PUBLIC
  src/
)

target_link_libraries(
  engine_vulkan PUBLIC
  volk
  vk-bootstrap::vk-bootstrap
  glfw
  spdlog::spdlog
)
