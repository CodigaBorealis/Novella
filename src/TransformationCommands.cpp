#include "../Novella/Commands/CommandContext.hpp"
#include "../Novella/Commands/TransformationCommands.hpp"
#include "../Novella/Attribute/Renderable.hpp"
#include "../Novella/Attribute/Layoutable.hpp"
#include "../Novella/Graphics/Color.hpp"
#include <cstdint>
#include <stdexcept>


namespace Novella::Commands{

    void resize(CommandContext& context, const nlohmann::json& args){

        auto& object = context.target<Attribute::Renderable>();

        
    }

    void move(CommandContext& context, const nlohmann::json& args){

        auto& object = context.target<Attribute::Layoutable>();

        Layout currentLayout = object.getLayout();
        //Do stuff
    }

    void setPosition(CommandContext& context, const nlohmann::json& args){

        
    }

    void setColor(CommandContext& context, const nlohmann::json& args){

        if(!args.is_object()) throw std::runtime_error("setColor: expected object");

        if(!args.contains("red")) throw std::runtime_error("setColor: missing argument 'red'");

        if(!args.at("red").is_number_unsigned()) throw std::runtime_error("setColor: expected unsigned int for argument 'red'");

        if(!args.contains("blue")) throw std::runtime_error("setColor: missing argument 'blue'");

        if(!args.at("blue").is_number_unsigned()) throw std::runtime_error("setColor: expected unsigned int for argument 'blue'");

        if(!args.contains("green")) throw std::runtime_error("setColor: missing argument 'green'");

        if(!args.at("green").is_number_unsigned()) throw std::runtime_error("setColor: expected unsigned int for argument 'green'");

        if(!args.contains("alpha")) throw std::runtime_error("setColor: missing argument 'alpha'");

        if(!args.at("alpha").is_number_unsigned()) throw std::runtime_error("setColor: expected unsigned int for argument 'alpha'");

        unsigned int r = args.at("red").get<unsigned int>();
        unsigned int g = args.at("green").get<unsigned int>();
        unsigned int b = args.at("blue").get<unsigned int>();
        unsigned int a = args.at("alpha").get<unsigned int>();

        if(r > 255) throw std::runtime_error("setColor: overflow for argument 'red' expected value is between 0 and 255");
        
        if(b > 255) throw std::runtime_error("setColor: overflow for argument 'blue' expected value is between 0 and 255");

        if(g > 255) throw std::runtime_error("setColor: overflow for argument 'green' expected value is between 0 and 255");

        if(a > 255) throw std::runtime_error("setColor: overflow for argument 'alpha' expected value is between 0 and 255");

        auto& object = context.target<Attribute::Renderable>();
        
            uint8_t red = args.at("red").get<uint8_t>();
            uint8_t green = args.at("green").get<uint8_t>();
            uint8_t blue = args.at("blue").get<uint8_t>();
            uint8_t alpha = args.at("alpha").get<uint8_t>();

            object.setColor({red, green, blue, alpha});
    }

    void setTransparency(CommandContext& context, const nlohmann::json& args){

        if(!args.is_object()) throw std::runtime_error("setTransparency: expected object");

        if(!args.contains("alpha")) throw std::runtime_error("setTransparency: missing argument 'alpha'");

        if(!args.at("alpha").is_number_unsigned()) throw std::runtime_error("setTransparency: expected unsigned int for argument 'alpha'");

        unsigned int a = args.at("alpha").get<unsigned int>();

        if(a > 255) throw std::runtime_error("setTransparency: overflow for argument 'alpha' expected value is between 0 and 255");

        auto& object = context.target<Attribute::Renderable>();
        
        uint8_t alpha = args.at("alpha").get<uint8_t>();

        Graphics::Color originalColor = object.getColor();

        object.setColor({originalColor.red, originalColor.green, originalColor.blue, alpha});

    }

    void setText(CommandContext& context, const nlohmann::json& args){

        
    }
}