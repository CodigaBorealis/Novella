#include "../Novella/Project/Parser.hpp"
#include "../Novella/Project/Lexer.hpp"
#include "../Novella/Project/EngineConfig.hpp"
#include <stdexcept>
#include <vector>
namespace Novella::Project{

    EngineConfig Parser::parse(){

        EngineConfig config{};

        while(current().type != Token::Type::EndOfFile){

            if(current().text == "Window"){

                registerSeenSection("Window");
                
                parseWindow(config);

            }else if(current().text == "Scenes"){

                registerSeenSection("Scenes");
                parseScenes(config);

            }else{

                throw std::runtime_error("Unexpected section: '" + current().text + "'");
            }
        }

        if(!seenProperties.contains("width")) throw std::runtime_error("Missing width property for window");
        
        if(!seenProperties.contains("height")) throw std::runtime_error("Missing width property for height");
        
        if(!seenProperties.contains("title")) throw std::runtime_error("Missing width property for title");

        return config;

    }

    Parser::Parser(Lexer& lexer){

        while(true){

            Token token = lexer.next();

            tokens.push_back(token);

            if(token.type == Token::Type::EndOfFile) break;
        }
    }

    Token& Parser::current(){

        return tokens[position];
    }

    Token& Parser::peek(size_t offset){

        if(position + offset >= tokens.size()) return tokens.back();

        return tokens[position + offset];
    }

    void Parser::consume(){

        if(position < tokens.size() - 1) ++ position;
    }

    void Parser::expect(Token::Type type){

        if(current().type != type) throw std::runtime_error("Unexpected token: " + current().text + " at position " + std::to_string(position) );

        consume();
    }

    void Parser::registerSeenSection(const std::string& section){

        auto& registry = parseRegistry.at(ParseRegistry::stringToSection(section));

        if(registry.firstDefinitionIndex == -1) registry.firstDefinitionIndex = position;//Is off by a lot but i will fix it later

        registry.evalCount ++;
    }

    void Parser::parseWindow(EngineConfig& config){

        expect(Token::Type::Identifier);
        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            if(current().type == Token::Type::EndOfFile) throw std::runtime_error("Unexpected end of file");

            if(current().text == "Flags"){

                parseFlags(config);

            }else{

                parseWindowProperty(config);
            }
        }

        expect(Token::Type::RBrace);
    }

    void Parser::parseScenes(EngineConfig& config){

        expect(Token::Type::Identifier);
        expect(Token::Type::LBrace);

        while (current().type != Token::Type::RBrace) {
        
        if(current().type == Token::Type::EndOfFile) throw std::runtime_error("Unexpected end of file");

        std::string sceneName = current().text;

        expect(Token::Type::Identifier);

        expect(Token::Type::Equals);

        std::string src = current().text;

        expect(Token::Type::String);
        
        config.sceneData.push_back({sceneName, src});
        
        }

        expect(Token::Type::RBrace);

    }

    void Parser::parseWindowProperty(EngineConfig& config){

        std::string key = current().text;

        expect(Token::Type::Identifier);
        expect(Token::Type::Equals);

        Value value = parseValue();

        if(!seenProperties.insert(key).second) throw std::runtime_error("Duplicate window property '" + key + "'" );

        if(key == "width"){

            if(!value.isInt()) throw std::runtime_error("Expected integer for property width");

            config.width = value.as<int>();

            return;
        }

        if(key == "height"){

            if(!value.isInt()) throw std::runtime_error("Expected integer for property height");

            config.height = value.as<int>();

            return;
        }

        if(key == "title"){

            if(!value.isString()) throw std::runtime_error("Expected string for property title");

            config.title = value.as<std::string>();

            return;
        }

        if(key == "targetFPS"){

            if(!value.isInt()) throw std::runtime_error("Expected int for property targetFPS");

            config.targetFPS = value.as<int>();

            return;
        }

        if(key == "icon"){

            if(!value.isString()) throw std::runtime_error("Expected string for property icon");

            config.icon = value.as<std::string>();

            return;
        }

        throw std::runtime_error("Unknown window property '" + key + "'");
    }

    void Parser::parseFlags(EngineConfig& config){

        expect(Token::Type::Identifier);
        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            if(current().type == Token::Type::EndOfFile) throw std::runtime_error("Unexpected end of file");

            auto it = optionalFlags.find(current().text);

            if(it == optionalFlags.end()) throw std::runtime_error("Unknown window flag '" + current().text + "'");

            config.flags |= it->second;

            consume();
        }

        expect(Token::Type::RBrace);
    }

    Value Parser::parseValue(){

        Value value{};

        if(current().type == Token::Type::String){

            value.data = current().text;

            consume();

            return value;
        }

        if(current().type == Token::Type::Number){

            value.data = std::stoi(current().text);

            consume();

            return value;
        }

        throw std::runtime_error("Invalid value");
    }
}
