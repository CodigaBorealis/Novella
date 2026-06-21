#pragma once
#include "../../Core/Math/Rectangle.hpp"
#include "../../Core/Math/Vector2x.hpp"

namespace Novella{

    struct Style;    

    class Scene;

}

namespace Novella{

    class LayoutSystem{

        public:
        
        Rectangle compute(const Style& style, const Vector2i& parentSize);

        static Rectangle computeLabel(const Style& style, const Vector2f& textSize,  const Vector2i& parentSize);

        void compute(const Scene& scene, const Vector2i& windowSize);


        private:

        static Vector2f computeSize(const Style& style, const Vector2i& parentSize);

        static Vector2f computePosition(const Style& style, const Vector2f& computedSize, const Vector2i& parentSize);
    };

}