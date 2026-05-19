#pragma once
#include "../Math/Rectangle.hpp"
#include "../Math/Vector2x.hpp"
#include "Layout.hpp"
#include "../Scene/Scene.hpp"

namespace Novella{

    class LayoutSystem{

        public:
        
        Math::Rectangle compute(const Layout& layout, const Math::Vector2i& parentSize);

        static Math::Rectangle computeLabel(const Layout& layout, const Math::Vector2f& textSize,  const Math::Vector2i& parentSize);

        void compute(const Scene& scene, const Math::Vector2i& windowSize);


        private:

        static Math::Vector2f computeSize(const Layout& layout, const Math::Vector2i& parentSize);

        static Math::Vector2f computePosition(const Layout& layout, const Math::Vector2f& computedSize, const Math::Vector2i& parentSize);
    };

}