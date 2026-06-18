#include "../Novella/Commands/DebuggingCommands.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

namespace Novella::Commands{

    void showMessage(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("showMessage: expected object");

        if(!args.contains("message")) throw std::runtime_error("showMessage: missing argument 'message'");
        
        if(!args.at("message").is_string()) throw std::runtime_error("showMessage: Expected a string'");
        
        std::cout << args.at("message") << "\n";
    }


}