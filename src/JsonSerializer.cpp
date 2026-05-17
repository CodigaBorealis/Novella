#include "../Novella/IO/JsonSerializer.hpp"
#include "../Novella/IO/JsonValidator.hpp"
#include <fstream>

namespace Novella::IO{
    //Why do i do this to myself
    JsonSerializer::JsonSerializer(const Rendering::ResourceManager& manager)
        :
        builder(manager)
        {}

    std::unique_ptr<Scene> JsonSerializer::deserializeScene(const nlohmann::json& data){
        //This only validates the object not the runtime behaviour
        if(!JsonValidator::validateScene(data)) throw std::runtime_error("JsonSerializer::deserializeScene: invalid object: " + data.dump(2));

        auto scene = builder.build(data);

        if(data.contains("bgm") && data.at("bgm").is_string()){
            
            scene->setBgm(data.at("bgm").get<std::string>());
        }

        return scene;

    }

    nlohmann::json JsonSerializer::serializeScene(const Scene& scene){

        nlohmann::json jsonScene;

        auto& objects = scene.objects();

        if(scene.getBgm()){

            jsonScene["bgm"] = scene.getBgm();//crashes here

        }

        for(const auto& obj : objects){

            jsonScene["objects"].push_back(

                {
                    {"type", obj->getType()},
                    {"properties", obj->serialize()}
                }
            );



        }

        return jsonScene;

    }
    
    void JsonSerializer::saveScene(const std::string& name, const std::filesystem::path& location, const Scene& scene){

        auto json = serializeScene(scene);

        std::filesystem::path outputPath = location / (name + ".json");
        std::ofstream output(outputPath);

        if(!output.is_open()) return;//Log error eventually

        output << json;

    }

    nlohmann::json JsonSerializer::loadScene(const std::filesystem::path& file){
        
        if(!std::filesystem::exists(file)){

            throw std::runtime_error("JsonSerializer::loadScene: file not found");
        };

        std::ifstream loadedFile(file);

        nlohmann::json data;

        try{

            loadedFile >> data;

        }catch(const nlohmann::json::parse_error& e){

            //Log an error eventually
            return nlohmann::json();
        }


        return data;
        
    }

    

}