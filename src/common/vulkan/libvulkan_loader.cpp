//
// Copyright 2021 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// libvulkan_loader.cpp:
//    Helper functions for the loading Vulkan libraries.
//

#include "common/vulkan/libvulkan_loader.h"

#include "common/system_utils.h"

#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <string>

static void print_message(std::string_view msg) {
    fwrite(msg.data(), 1, msg.size(), stdout);
}

#if !defined(ANGLE_PLATFORM_APPLE)
static void vulkan_load_from_pojavexec() {
    const char* turnipEnv = std::getenv("ANGLE_LOAD_TURNIP");

    if (!turnipEnv || std::string(turnipEnv) != "true") {
        return;
    }

    print_message("[ANGLE] Try to dlopen libpojavexec.\n");
    void* lib_handle = dlopen("libpojavexec.so", RTLD_NOLOAD);
    if (lib_handle == nullptr) {
        print_message("[ANGLE] Failed to dlopen libpojavexec, now try again.\n");
        lib_handle = dlopen("libpojavexec.so", RTLD_LOCAL | RTLD_LAZY);
        if (lib_handle == nullptr) {
            print_message("[ANGLE] Failed to dlopen libpojavexec. Are you using Pojav Glow Worm? Now try to dlopen libpgw.\n");
            lib_handle = dlopen("libpgw.so", RTLD_NOLOAD);
            if (lib_handle == nullptr) {
                print_message("[ANGLE] Failed to dlopen libpgw. Now try again.\n");
                lib_handle = dlopen("libpgw.so", RTLD_LOCAL | RTLD_LAZY);
            }
        }
    }

    void *(*load_vulkan_func)() = reinterpret_cast<void*(*)()>(
        lib_handle ? dlsym(lib_handle, "maybe_load_vulkan") : nullptr);
    if (load_vulkan_func) {
        (void)load_vulkan_func();
    }
}
#endif

namespace angle
{
namespace vk
{
void *OpenLibVulkan()
{
#if !defined(ANGLE_PLATFORM_APPLE)
    vulkan_load_from_pojavexec();
    print_message("[ANGLE] vulkan_loader will load libvulkan.\n");
#endif

    constexpr const char *kLibVulkanNames[] = {
#if defined(ANGLE_PLATFORM_WINDOWS)
        "vulkan-1.dll",
#elif defined(ANGLE_PLATFORM_APPLE)
        "libMoltenVK.dylib", "libvulkan.dylib", "libvulkan.1.dylib",
        // Fallback paths for static macOS builds where the Vulkan loader is bundled
        // in the "Libraries/" subdirectory but the host module (containing ANGLE)
        // is in the parent directory.
        "Libraries/libvulkan.dylib", "Libraries/libvulkan.1.dylib", "Libraries/libMoltenVK.dylib"
#else
        "libvulkan.so",
        "libvulkan.so.1",
#endif
    };

    const char *kLibVulkanName_env = std::getenv("ANGLE_LIBVULKAN_NAME");

    constexpr SearchType kSearchTypes[] = {
// On Android and Fuchsia we use the system libvulkan.
#if defined(ANGLE_USE_CUSTOM_LIBVULKAN)
        SearchType::ModuleDir,
#else
        SearchType::SystemDir,
#endif  // defined(ANGLE_USE_CUSTOM_LIBVULKAN)
    };

    for (angle::SearchType searchType : kSearchTypes)
    {
        for (const char *libraryName : kLibVulkanNames)
        {
            void *library = nullptr;
            if (kLibVulkanName_env) {
                library = OpenSystemLibraryWithExtension(kLibVulkanName_env, searchType);
            } else {
                library = OpenSystemLibraryWithExtension(libraryName, searchType);
            }
            if (library)
            {
                return library;
            }
        }
    }

    print_message("[ANGLE] ERROR: failed to load libvulkan or libMoltenVK.\n");
    return nullptr;
}
}  // namespace vk
}  // namespace angle
