#pragma once

#include "defines.h"

// clang-format off
#include <volk.h>
#include <VkBootstrap.h>
// clang-format on

#include <spdlog/spdlog.h>

#include <cstdlib>

#define VK_CHECK(__result__)                                                                                                         \
    do {                                                                                                                             \
        auto __temp__ = (__result__);                                                                                                \
        if (__temp__ != VK_SUCCESS) {                                                                                                \
            spdlog::error("[VULKAN ERROR]: {}:{}: {} is returning {}", __FILE__, __LINE__, #__result__, static_cast<i32>(__temp__)); \
            abort();                                                                                                                 \
        }                                                                                                                            \
    } while (0);
