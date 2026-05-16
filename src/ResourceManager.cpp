#include "../Novella/Rendering/ResourceManager.hpp"
#include <memory>
#include <nlohmann/json.hpp>

namespace Novella::Rendering{

        std::shared_ptr<Graphics::Image> ResourceManager::loadImage(const std::string& name, const std::filesystem::path& src){

        auto image = std::make_shared<Graphics::Image>(src);

        if(!image) throw std::runtime_error("Failed  to load an image: " + name);

        if(images.contains(name)) throw std::runtime_error("There is already a font with this name: " + name);

        ImageResource resource(src, image);

        images.emplace(name, std::move(resource));

        return image;
    }

    std::shared_ptr<Graphics::Texture>ResourceManager::loadTexture(const std::string& name, const std::filesystem::path& src){

        auto texture = std::make_shared<Graphics::Texture>(src);

        if(!texture) throw std::runtime_error("Failed  to load a texture: " + name);

        if(textures.contains(name)) throw std::runtime_error("There is already a texture with this name: " + name);

        TextureResource resource{src, texture};

        textures.emplace(name, std::move(resource));

        return texture;
    }

    std::shared_ptr<Graphics::Font> ResourceManager::loadFont(const std::string& name, const std::filesystem::path& src){

        auto font = std::make_shared<Graphics::Font>(src);

        if(!font) throw std::runtime_error("Failed  to load a font: " + name);

        if(fonts.contains(name)) throw std::runtime_error("There is already a font with this name: " + name);

        FontResource resource(src, font);

        fonts.emplace(name, std::move(resource));

        return font;
    }

    std::shared_ptr<Graphics::Texture> ResourceManager::getTexture(const std::string& name) const{

        if(!textures.contains(name)) throw std::runtime_error(name + " is not a registered texture");

        return textures.at(name).texture;
    }

    std::shared_ptr<Graphics::Font> ResourceManager::getFont(const std::string& name) const{

        if(!fonts.contains(name)) throw std::runtime_error(name + " is not a registered font");

        return fonts.at(name).font;

    }

    nlohmann::json ResourceManager::serialize() const{

        nlohmann::json data;

        data["textures"] = nlohmann::json::array();
        data["fonts"] = nlohmann::json::array();

        for(const auto& [id, texture] : textures){

            data["textures"].push_back({

                {"id", id},
                {"path",texture.src.string()}
            
            });
        }

        for(const auto& [id, font] : fonts){

            data["fonts"].push_back({

                {"id",id},
                {"path", font.src.string()}
            });
        }

        return data;
    }

    void ResourceManager::deserialize(const nlohmann::json& data){

        for(const auto& texture : data["textures"]){

            loadTexture(texture["id"], texture["path"]);
        }

        for(const auto& font : data["fonts"]){

            loadFont(font["id"], font["path"]);
        }
    }

    void ResourceManager::clear(){

        this->textures.clear();
        this->fonts.clear();
    }
}