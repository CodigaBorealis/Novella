#include "../Novella/Commands/CommandContext.hpp"
#include "../Novella/Commands/WindowCommands.hpp"
#include "../Novella/Window/Window.hpp"
#include <stdexcept>

namespace Novella::Commands{

    void setWindowTitle(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("setWindowTitle: expected object");

        if(!args.contains("title")) throw std::runtime_error("setWindowTitle: missing argument 'title'");

        if(!args.at("title").is_string()) throw std::runtime_error("setWindowTitle: expected string for argument 'title'");

        std::string title = args.at("title").get<std::string>();

        context.window->setTitle(title);
    }

    void setWindowIcon(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("setWindowIcon: expected object");

        if(!args.contains("src")) throw std::runtime_error("setWindowIcon: missing argument 'src'");

        if(!args.at("src").is_string()) throw std::runtime_error("setWindowTitle: expected string for argument 'src'");

        std::filesystem::path src{args.at("title").get<std::string>()};

        context.window->setIcon(src);
    }

    void setWindowPosition(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("setWindowPosition: expected object");

        if(!args.contains("x")) throw std::runtime_error("setWindowPosition: missing argument 'x'");

        if(!args.at("x").is_number_integer()) throw std::runtime_error("setWindowTitle: expected int for argument 'x'");

        if(!args.contains("y")) throw std::runtime_error("setWindowPosition: missing argument 'y'");

        if(!args.at("y").is_number_integer()) throw std::runtime_error("setWindowTitle: expected int for argument 'y'");

        int x = args.at("x").get<int>();
        int y = args.at("x").get<int>();

        context.window->setPosition({x, y});

    }

    void setWindowSize(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(!args.is_object()) throw std::runtime_error("setWindowSize: expected object");

        if(!args.contains("width")) throw std::runtime_error("setWindowSize: missing argument 'width'");

        if(!args.at("width").is_number_integer()) throw std::runtime_error("setWindowSize: expected int for argument 'width'");

        if(!args.contains("height")) throw std::runtime_error("setWindowSize: missing argument 'height'");

        if(!args.at("height").is_number_integer()) throw std::runtime_error("setWindowSize: expected int for argument 'height'");

        int width = args.at("width").get<int>();
        int height = args.at("height").get<int>();

        context.window->setPosition({width, height});

    }

    void closeWindow(const std::string& target,CommandContext &context, const nlohmann::json &args){

        if(args.size() != 0) throw std::runtime_error("closeWindow: expected 0 arguments, got: " + std::to_string(args.size()));

        context.window->close();
    }
}