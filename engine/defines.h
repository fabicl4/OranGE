#pragma once

// Precompiled header file for the OranGE engine.

// This file is a copy of the definition file of Kohi game engine
// link: https://github.com/travisvroman/kohi/blob/main/engine/src/defines.h

// Types
// ----------------------------------------

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef char b8;

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure all types are of the correct size.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

#define TRUE 1
#define FALSE 0

#define ArrayCount(arr) (sizeof((arr))) / (sizeof((arr)[0])))
#define KB(val) ((val) * 1024ull)
#define MB(val) (KB(val) * 1024ull)
#define GB(val) (GB(val) * 1024ull)

#define Align16(val) ((val + 15) & ~15)
#define Align8(val) ((val + 7) & ~7)
#define Align4(val) ((val + 3) & ~3)

// left-shift x bits.
#define BIT(x) 1 << x

/************************************
 *	DEFAULT INCLUDES
 ************************************/
#include <unordered_map>
#include <mutex>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <array>
#include <functional>
#include <algorithm>

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>