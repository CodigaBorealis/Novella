#pragma once
#include "../../Systems/Layout/Style.hpp"
#include "../../Core/Math/Rectangle.hpp"

namespace Novella::Traits{

    struct Layoutable{

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
        
        protected:

        Layoutable(const Style& style)
            :
            style(style)
            {}

            Style style;
            Rectangle computedRectangle;
    };
}