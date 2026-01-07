cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

project(testbed CXX)

add_executable(
  testbed
  src/main.cpp
)

target_link_libraries(
  testbed PRIVATE
  engine_vulkan
)
