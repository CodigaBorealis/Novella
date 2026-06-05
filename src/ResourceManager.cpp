#include "../Novella/Rendering/ResourceManager.hpp"
#include <cstddef>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
namespace Novella::Resources{

    ResourceManager::~ResourceManager(){

        clear();
    };
        void ResourceManager::loadImage(const std::string& name, const std::filesystem::path& src){

        auto image = std::make_shared<Graphics::Image>(src);

        if(!image) throw std::runtime_error("Failed  to load an image: " + name);

        if(imageResources.contains(name)) throw std::runtime_error("There is already a font with this name: " + name);

        ImageResource resource(src, image);

        imageResources.emplace(name, std::move(resource));

    }

    void ResourceManager::loadTexture(const std::string& name, const std::filesystem::path& src){

        if(!std::filesystem::exists(src)) throw std::runtime_error("File not found: " + src.string());

        auto texture = std::make_shared<Graphics::Texture>(src);

        if(!texture) throw std::runtime_error("Failed  to load a texture: " + name);

        if(textureResources.contains(name)) throw std::runtime_error("There is already a texture with this name: " + name);

        TextureResource resource{src, texture};

        textureResources.emplace(name, std::move(resource));

    }

    void ResourceManager::loadFont(const std::string& name, const std::filesystem::path& src){

        if(!std::filesystem::exists(src)) throw std::runtime_error("File not found: " + src.string());

        auto font = std::make_shared<Graphics::Font>(src);

        if(!font) throw std::runtime_error("Failed  to load a font: " + name);

        if(fontResources.contains(name)) throw std::runtime_error("There is already a font with this name: " + name);

        FontResource resource(src, font);

        fontResources.emplace(name, std::move(resource));

    }

    void ResourceManager::loadAudio(const std::string& name, const std::filesystem::path& src, const std::string& type){

        if(!std::filesystem::exists(src)) throw std::runtime_error("File not found: " + src.string());

        if(soundResources.contains(name)) throw std::runtime_error("There is already an audio resource with this name: " + name);

        if(type != "sfx" && type != "music") throw std::runtime_error("Invalid audio resource type '" + type + "'");

        AudioResource resource{name, src, type};

        soundResources.emplace(name, std::move(resource));

    }
    
    std::shared_ptr<Graphics::Texture> ResourceManager::getTexture(const std::string& name) const{

        if(!textureResources.contains(name)) throw std::runtime_error(name + " is not a registered texture");

        return textureResources.at(name).texture;
    }

    std::shared_ptr<Graphics::Font> ResourceManager::getFont(const std::string& name) const{

        if(!fontResources.contains(name)) throw std::runtime_error(name + " is not a registered font");

        return fontResources.at(name).font;

    }

    const ResourceManager::AudioResource& ResourceManager::getAudio(const std::string& name) const{

        if(!soundResources.contains(name)) throw std::runtime_error(name + " is not a registered audio resource");

        auto it = soundResources.find(name);

        return it->second;
    }
    
    void ResourceManager::clear(){

        this->soundResources.clear();
        this->imageResources.clear();
        this->textureResources.clear();
        this->fontResources.clear();
    }

    size_t ResourceManager::size() const{

        return imageResources.size() + textureResources.size() + fontResources.size() + soundResources.size();
    }
    
    std::unordered_map<std::string, ResourceManager::ImageResource>& ResourceManager::images(){

        return imageResources;
    }

    const std::unordered_map<std::string, ResourceManager::ImageResource>& ResourceManager::images() const{

        return imageResources;
    }
        
    const std::unordered_map<std::string, ResourceManager::TextureResource>& ResourceManager::textures() const{

        return textureResources;
    }

    std::unordered_map<std::string, ResourceManager::TextureResource>& ResourceManager::textures(){

        return textureResources;
    }
        
    const std::unordered_map<std::string, ResourceManager::FontResource>& ResourceManager::fonts() const{

        return fontResources;
    }

    std::unordered_map<std::string, ResourceManager::FontResource>& ResourceManager::fonts(){

        return fontResources;
    }

    const std::unordered_map<std::string, ResourceManager::AudioResource>& ResourceManager::audio() const{

        return soundResources;
    }

    std::unordered_map<std::string, ResourceManager::AudioResource>& ResourceManager::audio(){

        return soundResources;
    }
}