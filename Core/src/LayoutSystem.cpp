#include "../Novella/Systems/Layout/LayoutSystem.hpp"
#include <algorithm>
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Object.hpp"

namespace Novella{

    Rectangle LayoutSystem::compute(const Style& style, const Vector2i& parentSize){

        Vector2f size = computeSize(style, parentSize);
        
        Vector2f position = computePosition(style, size, parentSize);
        //Should probably cast to int

        Rectangle computedRectangle{position.x, position.y, size.x, size.y};

        return computedRectangle;
    }

    void LayoutSystem::compute(Scene& scene, const Vector2i& windowSize){
        //this does run
        if(!scene.needsSorting()) return;        

        scene.forEachObject([this, &windowSize](Traits::Object& object){

            if(auto* layoutable = dynamic_cast<Traits::Layoutable*>(&object)){

                layoutable->setComputedRectangle(compute(layoutable->getStyle(), windowSize));
            }
        });
    }

    Rectangle LayoutSystem::computeLabel(const Style& style, const Vector2f& textSize, const Vector2i& parentSize){

        Vector2f position = computePosition(style, textSize, parentSize);

        position.x += style.offset.x;

        position.y += style.offset.y;

        return{position.x, position.y, textSize.x, textSize.y};
    }

    Vector2f LayoutSystem::computeSize(const Style& style, const Vector2i& parentSize){

        float computedWidth = static_cast<float>(style.width);
        float parentWidth = static_cast<float>(parentSize.x);
        //Receives fixed somehow

        switch(style.widthMode){

            case SizeMode::Fixed:

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
        float parentHeight = static_cast<float>(parentSize.y);

        switch(style.heightMode){

            case SizeMode::Fixed:

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

        return {computedWidth, computedHeight};
    }

    Vector2f LayoutSystem::computePosition(const Style& style, const Vector2f& computedSize, const Vector2i& parentSize){

        float x = 0;
        float y = 0;

        switch(style.anchor){

            case Anchor::TopLeft:

                x = 0;
                y = 0;

                break;
            
            case Anchor::TopCenter:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = 0;
                
                break;

            case Anchor::TopRight:

                x = parentSize.x - computedSize.x;
                y = 0;
                
                break;
            
            case Anchor::CenterLeft:

                x = 0;
                y = (parentSize.y - computedSize.y) * 0.5f;
                
                break;
            
            case Anchor::Center:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = (parentSize.y - computedSize.y) * 0.5f;
                
                break;
            
            case Anchor::CenterRight:

                x = parentSize.x - computedSize.x;
                y = (parentSize.y - computedSize.y) * 0.5f;

                break;

            case Anchor::BottomLeft:

                x = 0;
                y = parentSize.y - computedSize.y;

                break;
            
            case Anchor::BottomCenter:

                x = (parentSize.x - computedSize.x) * 0.5f;
                y = parentSize.y - computedSize.y;

                break;

            case Anchor::BottomRight:

                x = parentSize.x - computedSize.x;
                y = parentSize.y - computedSize.y;

                break;
            
        }
        
        x += style.offset.x;
        y += style.offset.y;

        return {x, y};
    }

}