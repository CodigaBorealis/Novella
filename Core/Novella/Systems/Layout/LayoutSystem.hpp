#pragma once
#include "../../Core/Math/Rectangle.hpp"
#include "../../Core/Math/Vector2x.hpp"
#include <vector>

namespace Novella::Traits{

    struct Layoutable;
}

namespace Novella{

    struct Style;    

    class Scene;

}

namespace Novella{

    class LayoutSystem{

        public:
        
        Rectangle compute(const Style& style, const Rectangle& parentRectangle, const Rectangle& desiredSize);

        void compute(Scene& scene, const Rectangle& parentSize);


        private:    

        std::vector<Traits::Layoutable*> layoutCache;

        static Rectangle computeSize(const Style& style, const Rectangle& parentSize, const Rectangle& baseSize);

        static Rectangle computePosition(const Style& style, const Rectangle& computedSize, const Rectangle& parentSize);
    };

}