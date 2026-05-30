#pragma once
#include <nlohmann/json.hpp>
#include "../Math/Vector2x.hpp"

namespace Novella::Attribute{

    struct Clickable{

        public:

        virtual ~Clickable() = default;
                        
        virtual bool contains(const Math::Vector2f& mousePos) const = 0;
        
    };
}
