#pragma once
#include <cstdint>

namespace Novella{

    struct Handle{

        uint32_t index = 0;
        uint32_t generation = 0;
    };
}