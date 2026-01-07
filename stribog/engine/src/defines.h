#pragma once

#include <cstdint>
#include <expected>
#include <string>

#if defined(STRIBOG_WINDOWS)
#if defined(STRIBOG_EXPORT)
#define STRIBOG_API __declspec(dllexport)
#else
#define STRIBOG_API __declspec(dllimport)
#endif
#else
#define STRIBOG_API
#endif

#if defined(STRIBOG_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(STRIBOG_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_WAYLAND
#else
#error platform is not supported!
#endif

using i8 = int8_t;
using u8 = uint8_t;

using i16 = int16_t;
using u16 = uint16_t;

using i32 = int32_t;
using u32 = uint32_t;

using i64 = int64_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using String = std::string;

template<typename T, typename E>
using Result = std::expected<T, E>;

template<typename E>
using Error = std::unexpected<E>;
