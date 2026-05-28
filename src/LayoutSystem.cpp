#include "../Novella/Layout/LayoutSystem.hpp"
#include <algorithm>
#include "../Novella/Attribute/Layoutable.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Object.hpp"

namespace Novella{

    Math::Rectangle LayoutSystem::compute(const Layout& layout, const Math::Vector2i& parentSize){

        Math::Vector2f size = computeSize(layout, parentSize);
        
        Math::Vector2f position = computePosition(layout, size, parentSize);
        //Should probably cast to int

        Math::Rectangle computedRectangle{position.x, position.y, size.x, size.y};

        return computedRectangle;
    }

    void LayoutSystem::compute(const Scene& scene, const Math::Vector2i& windowSize){
        //this does run
        for(const auto& obj : scene.objects()){

            if(auto* layoutable = dynamic_cast<Attribute::Layoutable*>(obj.get())){

                layoutable->setComputedRectangle(compute(layoutable->getLayout(), windowSize));
            }
        }
    }

    Math::Rectangle LayoutSystem::computeLabel(const Layout& layout, const Math::Vector2f& textSize, const Math::Vector2i& parentSize){

        Math::Vector2f position = computePosition(layout, textSize, parentSize);

        position.x += layout.offset.x;

        position.y += layout.offset.y;

        return{position.x, position.y, textSize.x, textSize.y};
    }

    Math::Vector2f LayoutSystem::computeSize(const Layout& layout, const Math::Vector2i& parentSize){

        float computedWidth = static_cast<float>(layout.width);
        float parentWidth = static_cast<float>(parentSize.x);
        //Receives fixed somehow

        switch(layout.widthMode){

            case SizeMode::Fixed:

                break;
            
            case SizeMode::Percent:{

                float percent = std::clamp(layout.widthPercent, 0.0f, 100.f);

                computedWidth = parentWidth * (percent / 100.0f);

                break;
            }
            
            case SizeMode::FitWidth:

                computedWidth = parentWidth;

                break;
            
            default:
                
                break;
        }

        float computedHeight = static_cast<float>(layout.height);
        float parentHeight = static_cast<float>(parentSize.y);

        switch(layout.heightMode){

            case SizeMode::Fixed:

                break;
            
            case SizeMode::Percent:{

                float percent = std::clamp(layout.heightPercent, 0.0f, 100.f);

                computedHeight = parentHeight * (percent / 100.0f);
                
                break;
            }
            //this works
            case SizeMode::FitHeight:

                computedHeight = parentHeight;

                break;
            
            default:
                
                break;
        }

        return {computedWidth, computedHeight};
    }

    Math::Vector2f LayoutSystem::computePosition(const Layout& layout, const Math::Vector2f& computedSize, const Math::Vector2i& parentSize){

        float x = 0;
        float y = 0;

        switch(layout.anchor){

            case Anchor::TopLeft:

                x = 0;
                y = 0;

                break;
            
            case Novella::Anchor::TopCenter:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = 0;
                
                break;

            case Novella::Anchor::TopRight:

                x = parentSize.x - computedSize.x;
                y = 0;
                
                break;
            
            case Novella::Anchor::CenterLeft:

                x = 0;
                y = (parentSize.y - computedSize.y) * 0.5f;
                
                break;
            
            case Novella::Anchor::Center:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = (parentSize.y - computedSize.y) * 0.5f;
                
                break;
            
            case Novella::Anchor::CenterRight:

                x = parentSize.x - computedSize.x;
                y = (parentSize.y - computedSize.y) * 0.5f;

                break;

            case Novella::Anchor::BottomLeft:

                x = 0;
                y = parentSize.y - computedSize.y;

                break;
            
            case Novella::Anchor::BottomCenter:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = parentSize.y - computedSize.y;

                break;

            case Novella::Anchor::BottomRight:

                x = parentSize.x - computedSize.x;
                y = parentSize.y - computedSize.y;

                break;
            
        }
        
        x += layout.offset.x;
        y += layout.offset.y;

        return {x, y};
    }

}