#include "../Novella/Commands/InputCommands.hpp"
#include "../Novella/Commands/CommandContext.hpp"
#include "../Novella/Input/InputSystem.hpp"

namespace Novella::Commands{

    void setMousePosition(uint64_t target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("setMousePosition: expected object");

        if(!args.contains("x")) throw std::runtime_error("setMousePosition: missing argument 'x'");

        if(!args.at("x").is_number_float())  throw std::runtime_error("setMousePosition: expected float for argument 'x'");

        if(!args.contains("y")) throw std::runtime_error("setMousePosition: missing argument 'y'");

        if(!args.at("y").is_number_float())  throw std::runtime_error("setMousePosition: expected float for argument 'y'");
        
        float x = args.at("x").get<float>();
        float y = args.at("y").get<float>();

        Input::InputSystem::setMousePosition({x, y});
    }

    void showCursor(uint64_t target,CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("showCursor: expected 0 arguments, got: " + std::to_string(args.size()));

        Input::InputSystem::showCursor();
    }

    void hideCursor(uint64_t target,CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("hideCursor: expected 0 arguments, got: " + std::to_string(args.size()));

        Input::InputSystem::hideCursor();
    }

    void enableCursor(uint64_t target,CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("enableCursor: expected 0 arguments, got: " + std::to_string(args.size()));

        Input::InputSystem::enableCursor();
    }
    
    void disableCursor(uint64_t target,CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("disableCursor: expected 0 arguments, got: " + std::to_string(args.size()));

        Input::InputSystem::disableCursor();
    }
}