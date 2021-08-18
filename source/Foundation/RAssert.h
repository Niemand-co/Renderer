#pragma once
#include "Platform.h"
#include "BuildType.h"

#if defined(RENGINE_WINDOWS)
#include <cassert>
#define RENGINE_ASSERT_IMPL(EXPR) assert(EXPR)

#elif defined(RENGINE_MACOS)
#define RENGINE_ASSERT_IMPL(EXPR)

#else
#endif

#if defined(RENGINE_DEBUG)
#define RENGINE_ASSERT(EXPR) RENGINE_ASSERT_IMPL(EXPR)

#elif defined(RENGINE_RELEASE)
#define RENGINE_ASSERT(EXPR) ((void)0)

#else
#endif