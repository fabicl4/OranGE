#pragma once

#include "defines.h"

namespace OranGE {

struct Shader
{
    u32 id;
    u32 type; // e.g. GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.
    char* debugName = nullptr; // optional name for debugging purposes
};

};