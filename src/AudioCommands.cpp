#include "../Novella/Commands/AudioCommands.hpp"
#include "../Novella/Commands/CommandContext.hpp"
#include "../Novella/Audio/AudioSystem.hpp"
#include <stdexcept>
#include <string>

namespace Novella::Commands{

    void playSound(CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("playSound: expected object");

        if(!args.contains("id")) throw std::runtime_error("playSound: missing argument 'id'");

        if(!args.at("id").is_string()) throw std::runtime_error("playSound: expected string for argument 'id'");

        if(!context.audio) throw std::runtime_error("playSound: audio not initialized");

        std::string resourceID = args.at("id").get<std::string>();

        context.audio->play(resourceID);
    }

    void playMusic(CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("playMusic: expected object");

        if(!args.contains("id")) throw std::runtime_error("playMusic: missing argument 'id'");

        if(!args.at("id").is_string()) throw std::runtime_error("playMusic: expected string for argument 'id'");

        if(!context.audio) throw std::runtime_error("playMusic: audio not initialized");

        std::string resourceID = args.at(0).get<std::string>();

        stopMusic(context, nlohmann::json{});

        context.audio->play(resourceID);
    }

    void stopSound(CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("stopSound: expected object");

        if(!args.contains("id")) throw std::runtime_error("stopSound: missing argument 'id'");

        if(!args.at("id").is_string()) throw std::runtime_error("stopSound: expected string for argument 'id'");

        if(!context.audio) throw std::runtime_error("stopSound: audio not initialized");

        std::string resourceID = args.at(0).get<std::string>();

        context.audio->stop(resourceID);
    }

    void stopMusic(CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("stopMusic: expected 0 arguments, got: " + std::to_string(args.size()));

        if(!context.audio) throw std::runtime_error("stopSound: audio not initialized");

        auto currentBgm = context.audio->getCurrentBgm();

        if(!currentBgm) return;

        context.audio->stop(currentBgm.value());
    }

}