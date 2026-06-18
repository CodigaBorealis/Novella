#include "../Novella/Commands/CommandTable.hpp"
#include <stdexcept>

namespace Novella::Commands{

    void CommandTable::execute(const std::string& name, const std::string& target, CommandContext& context, const nlohmann::json& args){

        auto it = commands.find(name);

        if(it == commands.end()) throw std::runtime_error("Invalid internal command: " + name);

        it->second(target,context, args);
    }

}
