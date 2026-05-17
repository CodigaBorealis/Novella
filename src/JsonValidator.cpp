#include "../Novella/IO/JsonValidator.hpp"

namespace Novella::IO::JsonValidator {

        bool validateVector(const nlohmann::json& props, const std::string& key){

        if(!props.contains(key) || !props[key].is_array()) return false;

        if(props[key].size() != 2) return false;

        if(!props[key][0].is_number() || !props[key][1].is_number()) return false;

        return true;

    }

    bool validateBinds(const nlohmann::json& props){

        if(props.contains("keybinds")){

            for(const auto& bind : props["keybinds"]){

                if(!bind.contains("key") || !bind["key"].is_number_integer()) return false;

                if(!bind.contains("action") || !bind["action"].is_string()) return false;
            }
        }

        if(props.contains("mouseBinds")){

            for(const auto& bind : props["mouseBinds"]){

                if(!bind.contains("button") || !bind["button"].is_number_integer()) return false;

                if(!bind.contains("action") || !bind["action"].is_string()) return false;
            }
        }

        return true;
    }

    bool validateObject(const std::string& type, const nlohmann::json& props){

        if(type == "Background"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;

            if(!props.contains("id") || !props["id"].is_string()) return false;

            if(!props.contains("sprite") || !props["sprite"].is_string()) return false;

            if(!props.contains("colorMask") || !props["colorMask"].is_array()) return false;
            
            return true;
        }

        if(type == "Character"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;

            if(!props.contains("id") || !props["id"].is_string()) return false;

            if(!props.contains("sprite") || !props["sprite"].is_string()) return false;

            if(!validateVector(props, "dimensions")) return false;

            if(!validateVector(props, "position")) return false;
            
            if(!props.contains("colorMask") || !props["colorMask"].is_array()) return false;


            return true;
        }

        if(type == "DialogueBox"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;

            if(!props.contains("id") || !props["id"].is_string()) return false;

            if(!props.contains("sprite") || !props["sprite"].is_string()) return false;

            if(!validateVector(props, "dimensions")) return false;

            if(!props.contains("font") || !props["font"].is_string()) return false;

            if(!validateVector(props, "textOffset")) return false;

            if(!validateVector(props, "position")) return false;

            if(!validateBinds(props)) return false;

            if(!props.contains("colorMask") || !props["colorMask"].is_array()) return false;

            return true;
        }

        if(type == "Button"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;

            if(!props.contains("id") || !props["id"].is_string()) return false;

            if(!validateVector(props, "position")) return false;
            
            if(!props.contains("sprite") || !props["sprite"].is_string()) return false;

            if(!validateVector(props, "dimensions")) return false;

            if(!props.contains("state") || !props["state"].is_number_integer()) return false;

            if(!validateBinds(props)) return false;

            if(!props.contains("colorMask") || !props["colorMask"].is_array()) return false;


            return true;
        }

        if(type == "Label"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;

            if(!props.contains("id") || !props["id"].is_string()) return false;

            if(!validateVector(props, "position")) return false;
            
            if(!props.contains("font") || !props["font"].is_string()) return false;

            if(!props.contains("text") || !props["text"].is_string()) return false;

            if(!props.contains("fontSize") || !props["fontSize"].is_number_integer()) return false;
            
            if(!validateBinds(props)) return false;

            return true;
        }

        if(type == "Menu"){

            if(!props.contains("renderLayer") || !props["renderLayer"].is_number_integer()) return false;
            
            if(!props.contains("id") || !props["id"].is_string()) return false;
            
            if(!props.contains("visible") || !props["visible"].is_boolean()) return false;

            if(!props.contains("pauseGame") || !props["pauseGame"].is_boolean()) return false;

            if(!props.contains("isLocked") || !props["isLocked"].is_boolean()) return false;

            if(!props.contains("sprite") || !props["sprite"].is_string()) return false;

            if(!validateVector(props, "position")) return false;
            
            if(!validateVector(props, "dimensions")) return false;

            if(props.contains("buttons") && props["buttons"].is_array()){

                for(const auto& button: props["buttons"]){

                    if(!validateObject("Button", button)) return false;
                }
            }

            return true;
        }

        return false;
    }

    bool validateScene(const nlohmann::json& data){

        if(!data.is_object()) return false;

        if(!data.contains("objects") || !data["objects"].is_array()) return false;

        //if(!data.contains("resources")) return false;

        for(const auto& obj : data["objects"]){

            if(!obj.is_object()) return false;

            if(!obj.contains("type") || !obj["type"].is_string()) return false;

            if(!obj.contains("properties") || !obj["properties"].is_object()) return false;

            if(!validateObject(obj["type"], obj["properties"])) return false;
        }

        return true;

    }

}