#include "../Novella/Components/Traits/Composite.hpp"
#include <algorithm>
#include <memory>
#include <string>

namespace Novella::Traits{

    void Composite::addChild(const std::string& name, std::unique_ptr<Object> object){

        children.emplace(name, std::move(object));
    }

    const Object* Composite::getChild(const std::string& name) const{

        auto it = children.find(name);

        return it == children.end() ? nullptr : it->second.get();
    }
//I should later optimize this since it might make the renderer cache useless
    void Composite::draw(Renderer& renderer){
        
        //std::cout << "COMPOSITE : " << std::to_address(this) << " Children:\n";

        for(auto& [name, child] : children){

            //std::cout << "NAME: " << name << "ADDRESS: "<<std::to_address(child) << "\n";

           if(auto* renderable = dynamic_cast<Renderable*>(child.get())){

            renderable->draw(renderer); 
            
           } 
        }
        renderer.drawRectangle(computedRectangle, Colors::Blue);

    }

    void Composite::updateLayout(LayoutSystem& layout, const Rectangle& parent){

        Vector2f preferred = measure(layout);

        Rectangle rect = layout.compute(style, parent, {0, 0, preferred.x, preferred.y});

        setComputedRectangle(rect);

        for(auto& [name, child] : children){

            if(auto* layoutable = dynamic_cast<Layoutable*>(child.get())){

                layoutable->updateLayout(layout, rect);
            }
        }
    }

    Rectangle Composite::naturalSize() const{

        return {0, 0, static_cast<float>(style.width), static_cast<float>(style.height)};
    }

    std::unordered_map<std::string, std::unique_ptr<Object>>& Composite::getChildren(){

        return children;
    }

    Vector2f Composite::measure(LayoutSystem& layoutSystem) const{

        float minX = 0;
        float minY = 0;
        float maxX = 0;
        float maxY = 0;

        for(auto&[name, child] : children){

            auto* layoutable = dynamic_cast<Layoutable*>(child.get());

            if(!layoutable) continue;

            Vector2f contentSize = layoutable->measure(layoutSystem);

            const Style& childStyle = layoutable->getStyle();

            float resolvedWidth = (childStyle.widthMode == SizeMode::Fixed) ? childStyle.width : contentSize.x;
            float resolvedHeight = (childStyle.heightMode == SizeMode::Fixed) ? childStyle.height : contentSize.y;

            float childRight = childStyle.offset.x + resolvedWidth;
            float childBottom = childStyle.offset.y + resolvedHeight;

            minX = std::min(minX, static_cast<float>(childStyle.offset.x));
            minY = std::min(minY, static_cast<float>(childStyle.offset.y));

            maxX = std::max(maxX, childRight);
            maxY = std::max(maxY, childBottom);

        }

        return {maxX - minX, maxY - minY};
    }
}