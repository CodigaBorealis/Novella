#pragma once
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "ImageResource.hpp"
#include "AudioResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"

namespace Novella{

    class ResourceManager{

        public:

        ~ResourceManager();
        
        ResourceManager() = default;

        void loadImage(const std::string& name, const std::filesystem::path& src);
        
        void loadTexture(const std::string& name, const std::filesystem::path& src);

        void loadFont(const std::string& name, const std::filesystem::path& src);

        void loadAudio(const std::string& name, const std::filesystem::path& src, const std::string& type);

        std::shared_ptr<Image> getImage(const std::string& name) const;

        std::shared_ptr<Texture> getTexture(const std::string& name) const;

        std::shared_ptr<Font> getFont(const std::string& name) const;

        const AudioResource& getAudio(const std::string& name) const;
        
        std::unordered_map<std::string, ImageResource>& images();

        const std::unordered_map<std::string, ImageResource>& images() const;
        
        const std::unordered_map<std::string, TextureResource>& textures() const;

        std::unordered_map<std::string, TextureResource>& textures();
        
        const std::unordered_map<std::string, FontResource>& fonts() const;

        std::unordered_map<std::string, FontResource>& fonts();

        const std::unordered_map<std::string, AudioResource>& audio() const;

        std::unordered_map<std::string, AudioResource>& audio();

        void clear();

        size_t size() const;

        private:
        std::unordered_map<std::string, ImageResource> imageResources;
        std::unordered_map<std::string, TextureResource> textureResources;
        std::unordered_map<std::string, FontResource> fontResources;
        std::unordered_map<std::string, AudioResource> soundResources;
    };
}