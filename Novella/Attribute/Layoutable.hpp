#pragma once
#include "../Layout/Layout.hpp"
#include "../Math/Rectangle.hpp"

namespace Novella::Attribute{

    class Layoutable {

        protected:

        Layoutable(const Layout& layout)
            :
            layout(layout)
            {}

            Layout layout;
            Math::Rectangle computedRectangle;

        public:

            void setLayout(const Layout& layout){

                this->layout = layout;
            }

            const Layout& getLayout() const{

                return this->layout;
            }

            void setComputedRectangle(const Math::Rectangle& computedRectangle){

                this->computedRectangle = computedRectangle;
            }

            const Math::Rectangle& getComputedRectangle() const{

                return this->computedRectangle;
            }
            
        };

}