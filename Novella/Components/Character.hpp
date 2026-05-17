#pragma once
#include "../Graphics/Texture.hpp"
#include "Object.hpp"
#include "Renderable.hpp"
#include "Transformable.hpp"
#include "Type.hpp"
#include <memory>

namespace Novella::Components{

    class Character : public Attribute::Object, public Attribute::Transformable, public Attribute::Renderable{

        public:

            Character() = delete;

            Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position);
            Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position, int renderLayer, const Math::Vector2i& dimensions);
            
            std::string getID() const override;

            void draw(Rendering::Renderer& renderer) override;

            int renderLayer() const override;

            void setPosition(const Math::Vector2i& position) override;

            const Math::Vector2i& getPosition() const override;

            nlohmann::json serialize() const override;

            void setDimensions(const Math::Vector2i& dimensions) override;

            const Math::Vector2i& getDimensions() const override;

            const std::string getType() const override;

            void setColor(const Graphics::Color& color) override;

            const Graphics::Color& getColor() const override;

        private:

            std::string id;
            std::shared_ptr<Graphics::Texture> texture;
            Math::Vector2i position;
            int rLayer = 0;
            Math::Vector2i dimensions{};
            Graphics::Color tint;

            //std::vector<std::string> sounds;
        static constexpr const char* type = Type::Character;//This is shit but i need a way to serialize components

    };
}