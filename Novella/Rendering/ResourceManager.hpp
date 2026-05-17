#pragma once
#include "../Graphics/Image.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Font.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>

namespace Novella::Rendering{

    class ResourceManager{

        private:

        struct ImageResource{

            std::filesystem::path src;
            std::shared_ptr<Graphics::Image> image;

        };

        struct TextureResource{

            std::filesystem::path src;
            std::shared_ptr<Graphics::Texture> texture;

        };

        struct FontResource{
            
            std::filesystem::path src;
            std::shared_ptr<Graphics::Font> font;
        };
        
        public:

        ~ResourceManager();
        
        ResourceManager() = default;

        std::shared_ptr<Graphics::Image> loadImage(const std::string& name, const std::filesystem::path& src);
        
        std::shared_ptr<Graphics::Texture> loadTexture(const std::string& name, const std::filesystem::path& src);

        std::shared_ptr<Graphics::Font> loadFont(const std::string& name, const std::filesystem::path& src);

        std::shared_ptr<Graphics::Image> getImage(const std::string& name) const;

        std::shared_ptr<Graphics::Texture> getTexture(const std::string& name) const;

        std::shared_ptr<Graphics::Font> getFont(const std::string& name) const;

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json& data);

        void clear();

        private:
        std::unordered_map<std::string, ImageResource> images;
        std::unordered_map<std::string, TextureResource> textures;
        std::unordered_map<std::string, FontResource> fonts;

    };
}