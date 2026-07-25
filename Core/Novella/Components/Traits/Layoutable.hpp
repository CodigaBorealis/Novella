#pragma once
#include "../../Systems/Layout/LayoutSystem.hpp"
#include "../../Systems/Layout/Style.hpp"
#include "../../Core/Math/Rectangle.hpp"

namespace Novella::Traits{

    struct Layoutable{
        
        virtual ~Layoutable() = default;

        virtual void updateLayout(LayoutSystem& layoutSystem, const Rectangle& parentRectangle) = 0;

        virtual Vector2f measure(LayoutSystem& layoutSystem) const = 0;

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
        
        virtual Rectangle naturalSize() const = 0;
      
        protected:

            Style style;
            Rectangle computedRectangle;
    };
}