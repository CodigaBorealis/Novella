#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>

namespace Novella::Audio{
/**
 * @struct AudioResource
 * @brief Class that represents an item the AudioBackend must consume.
 */
    struct AudioResource{

        enum class AssetType{
            
        Music,
        SFX
     };
    
        AudioResource() = delete;
        AudioResource(const std::string& name, const std::filesystem::path& src, AssetType type)
            :
            name(name),
            src(src),
            type(type)
            {}

        nlohmann::json toJson() const {
        
            return {

            {"id", name},
            {"path", src.string()},
            {"type", static_cast<int>(type)},
            {"volume", defaultVolume},
            {"pitch", defaultPitch},
            {"pan", defaultPan}

            };
        }
        
        std::string name;
        std::filesystem::path src;        
        AssetType type;
        unsigned int id = 0;

        float defaultVolume = 1.0f;
        float defaultPitch = 1.0f;
        float defaultPan = 1.0f;
    };
}