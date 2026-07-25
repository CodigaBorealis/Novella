#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <algorithm>
#include <raylib.h>
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Object.hpp"

namespace Novella{

    Rectangle LayoutSystem::compute(const Style& style, const Rectangle& parentSize, const Rectangle& desiredSize){

        Rectangle size = computeSize(style, parentSize, desiredSize);
        
        Rectangle position = computePosition(style, size, parentSize);

        Rectangle computedRectangle{position.x, position.y, size.width, size.height};

        return computedRectangle;
    }

    void LayoutSystem::compute(Scene& scene, const Rectangle& parentRectangle){
        
        if(!scene.needsSorting()) return;        

        scene.forEachRootObject([this, &parentRectangle](Traits::Object& object){

            if(auto* layoutable = dynamic_cast<Traits::Layoutable*>(&object)){

                Vector2f size =  layoutable->measure(*this);
                
                layoutable->updateLayout(*this, parentRectangle);
            }
        });
    }

    Rectangle LayoutSystem::computeSize(const Style& style, const Rectangle& parentSize, const Rectangle& baseSize){

        float computedWidth = parentSize.width;
        float parentWidth = parentSize.width;

        switch(style.widthMode){

            case SizeMode::Fixed:

                computedWidth = style.width;

                break;
            
            case SizeMode::FitContent:

                computedWidth = baseSize.width;

                break;

            case SizeMode::Percent:{

                float percent = std::clamp(style.widthPercent, 0.0f, 100.f);

                computedWidth = parentWidth * (percent / 100.0f);

                break;
            }
            
            case SizeMode::FitWidth:

                computedWidth = parentWidth;

                break;
            
            default:
                
                break;
        }

        float computedHeight = static_cast<float>(style.height);
        float parentHeight = parentSize.height;

        switch(style.heightMode){

            case SizeMode::Fixed:

                computedHeight = style.height;
                break;

            case SizeMode::FitContent:

                computedHeight = baseSize.height;

                break;

            case SizeMode::Percent:{

                float percent = std::clamp(style.heightPercent, 0.0f, 100.f);

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

        Rectangle size{};

        size.width = computedWidth;
        size.height = computedHeight;

        return size;
    }

    Rectangle LayoutSystem::computePosition(const Style& style, const Rectangle& computedSize, const Rectangle& parentSize){

        float x = parentSize.x + (parentSize.width - computedSize.width) * 0.5f;

        float y = parentSize.y + (parentSize.height - computedSize.height) * 0.5f;

        switch(style.anchor){

            case Anchor::TopLeft:

                x = parentSize.x;
                y = parentSize.y;

                break;
            
            case Anchor::TopCenter:

                x = parentSize.x + (parentSize.width - computedSize.width) * 0.5f;
                y = parentSize.y;
                
                break;

            case Anchor::TopRight:

                x = parentSize.x + parentSize.width - computedSize.width;
                y = parentSize.y;
                
                break;
            
            case Anchor::CenterLeft:

                x = parentSize.x;
                y = parentSize.y + (parentSize.height - computedSize.height) * 0.5f;
                
                break;
            
            case Anchor::Center:

                x = parentSize.x + (parentSize.width - computedSize.width) * 0.5f;
                y = parentSize.y + (parentSize.height - computedSize.height) * 0.5f;
                
                break;
            
            case Anchor::CenterRight:

                x = parentSize.x + parentSize.width - computedSize.width;
                y = parentSize.y + (parentSize.height - computedSize.height) * 0.5f;

                break;

            case Anchor::BottomLeft:

                x = parentSize.x;
                y = parentSize.y + parentSize.height - computedSize.height;

                break;
            
            case Anchor::BottomCenter:

                x = parentSize.x + (parentSize.width - computedSize.width) * 0.5f;
                y = parentSize.y + parentSize.height - computedSize.height;

                break;

            case Anchor::BottomRight:

                x = parentSize.x + parentSize.width - computedSize.width;
                y = parentSize.y + parentSize.height - computedSize.height;

                break;
            
        }
        
        x += style.offset.x;
        y += style.offset.y;

        Rectangle position{};

        position.x = x;
        position.y = y;
        
        return position;
    }

}