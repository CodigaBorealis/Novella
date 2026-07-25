#pragma once
#include "Object.hpp"
#include "Renderable.hpp"
#include "Layoutable.hpp"
#include <memory>
#include <unordered_map>
#include <utility>

namespace Novella::Traits{

    struct Composite : Traits::Renderable, public Traits::Layoutable{

        template<class T>

        const T* childAs(const std::string& name) const{

            auto it = children.find(name);

            if(it == children.end()) return nullptr;

            if(it->second->getTypeID() != T::getStaticTypeID()) return nullptr;

            return static_cast<T*>(it->second.get());
        }

        template<class T>

        T* childAs(const std::string& name){

            return const_cast<T*>(std::as_const(*this).template childAs<T>(name));
        }

        virtual ~Composite() = default;

        void addChild(const std::string& name, std::unique_ptr<Object> object);

        const Object* getChild(const std::string& name) const;

        void draw(Renderer& renderer) override;

        void updateLayout(LayoutSystem& layout, const Rectangle& parent) override;
        
        Vector2f measure(LayoutSystem& layoutSystem) const override;

        Rectangle naturalSize() const override;

        std::unordered_map<std::string, std::unique_ptr<Object>>& getChildren();

        protected:

        std::unordered_map<std::string, std::unique_ptr<Object>> children;

        Rectangle boundaries;
    };
}