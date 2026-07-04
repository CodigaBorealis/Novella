#pragma once
#include <cstdint>
#include "../Components/Traits/Object.hpp"
#include <memory>
#include <string>

namespace Novella{

    struct Slot{

        std::unique_ptr<Novella::Traits::Object> object;
        uint32_t generation = 1;
        std::string name;
    };
}