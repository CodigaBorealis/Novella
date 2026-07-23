#pragma once
#include "../../Systems/Layout/LayoutSystem.hpp"
#include "../../Systems/Layout/Style.hpp"
#include "../../Core/Math/Rectangle.hpp"

namespace Novella::Traits{

    struct Layoutable{
        
        virtual ~Layoutable() = default;

        virtual void updateLayout(LayoutSystem& layoutSystem, const Vector2i& parentSize){

            computedRectangle = layoutSystem.compute(getStyle(), parentSize);
        }

        void setStyle(const Style& style){

            this->style = style;
        }

        const Style& getStyle() const{

            return this->style;
        }

        void setComputedRectangle(const Rectangle& computedRectangle){

            this->computedRectangle = computedRectangle;
        }

        const Rectangle& getComputedRectangle() const{

            return this->computedRectangle;
        }
            
        private:

            Style style;
            Rectangle computedRectangle;
    };
}