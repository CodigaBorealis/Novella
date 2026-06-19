#include "../Novella/Commands/CommandTable.hpp"
#include <stdexcept>
#include "../Novella/Commands/CommandContext.hpp"
namespace Novella::Commands{

    void CommandTable::execute(const std::string& name, const std::string& target, const nlohmann::json& args){

        auto it = commands.find(name);

        if(it == commands.end()) throw std::runtime_error("Invalid internal command: " + name);

        CommandContext context{nullptr, nullptr, nullptr, nullptr};
        
        it->second(target,context, args);
    }

}
