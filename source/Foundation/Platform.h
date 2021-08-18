#pragma once

#define RENGINE_PLATFORM_UNKNOWN "unknown"
#define RENGINE_PLATFORM_Windows "windows"
#define RENGINE_PLATFORM_MACOS   "macos"
#define RENGINE_PLATFORM_IOS     "ios"
#define RENGINE_PLATFORM_ANDROID "android"

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    #define RENGINE_PLATFORM
    #define RENGINE_WINDOWS
#elif defined(__APLLE__)
    #define RENGINE_PLATFORM
    #define RENGINE_MACOS
#else
    #define RENGINE_PALFORM
    #define RENGINE_UNKNOWN
#endif

#if defined(RENGINE_WINDOWS)
    #include "Platform/Windows.h"
#elif defined(RENGINE_MACOS)
    #include "Platform/Macos.h"
#else
#endif