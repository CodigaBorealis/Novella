#include "../Novella/Syntax/Scene/Parser.hpp"
#include "../Novella/Syntax/Scene/Lexer.hpp"
#include "../Novella/Syntax/Scene/SceneDefinition.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
//I hate this so much
namespace Novella::Syntax::Scene{

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

        if(current().type != type) throw std::runtime_error("Unexpected token: " + current().text);

        consume();
    }

    SceneDefinition Parser::parse(){

        return parseScene();
    }

    SceneDefinition Parser::parseScene(){

        if(current().text != "scene") throw std::runtime_error("Expected scene section");

        consume();

        SceneDefinition scene{};

        std::string sceneName = current().text;

        scene.name = sceneName;

        expect(Token::Type::Identifier);

        expect(Token::Type::LBrace);

        if(current().text != "resources") throw std::runtime_error("Expected resources section");

        parseResources(scene);

        if(current().text != "input") throw std::runtime_error("Expected input section");

        parseInput(scene); 

        while(current().type != Token::Type::RBrace){

            scene.objects.push_back(parseObject());

        }

        expect(Token::Type::RBrace);

        return scene;

    }

    void Parser::parseResources(SceneDefinition& scene){

        expect(Token::Type::Identifier);
        
        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            ResourceDefinition resource{};

            resource.type = current().text;

            expect(Token::Type::Identifier);

            resource.name = current().text;

            expect(Token::Type::Identifier);

            expect(Token::Type::Equals);

            resource.path = current().text;

            expect(Token::Type::String);

            scene.resources.push_back(resource);
        }

        expect(Token::Type::RBrace);

    }

    void Parser::parseInput(SceneDefinition& scene){

        expect(Token::Type::Identifier);

        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            InputBindingDefinition binding{};

            if(current().text != "click" && current().text != "key") throw std::runtime_error("Expected 'click' or 'key'");

            binding.inputType = current().text;

            consume();

            binding.input = current().text;

            expect(Token::Type::Identifier);

            expect(Token::Type::LBrace);

            while(current().type != Token::Type::RBrace){

                std::string property = current().text;

                expect(Token::Type::Identifier);

                expect(Token::Type::Equals);

                std::string value = current().text;

                consume();

                if(property == "alias"){

                    binding.commandAlias = value;

                }else if (property == "id"){

                    binding.targetName = value;
                }
            }

            expect(Token::Type::RBrace);

            scene.inputs.push_back(binding);
        }

        expect(Token::Type::RBrace);
    }

    ObjectDefinition Parser::parseObject(){

        ObjectDefinition object{};

        object.objectType = current().text;

        expect(Token::Type::Identifier);
        
        if(current().type == Token::Type::Identifier){

            object.objectName = current().text;

            expect(Token::Type::Identifier);
        }

        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            size_t startPosition = position;//To avoid looping forever if the parser gets stuck on a token

            if(current().type == Token::Type::Identifier && peek(1).type == Token::Type::Equals){

                object.properties.push_back(parseProperty());

            }else if(current().type == Token::Type::Identifier){

                object.children.push_back(parseObject());

            }else{

                throw std::runtime_error("Unexpected token inside object body: '" + current().text + "' at index " + std::to_string(position));
            }

            if(position == startPosition) throw std::runtime_error("Parser error: Stalled at token '" + current().text + "'");

        }

        expect(Token::Type::RBrace);

        return object;

    }

    Property Parser::parseProperty(){

        Property property{};

        property.name = current().text;

        expect(Token::Type::Identifier);

        expect(Token::Type::Equals);

        property.value = parseValue();

        return property;

    }

    Value Parser::parseValue(){

        Value value{};

        if(current().type == Token::Type::String){

            value.type = Value::Type::String;
            value.StringValue = current().text;

            consume();

            return value;
        }

        if(current().type == Token::Type::LParen){
            
            value.type = Value::Type::Array;
            
            consume();
            
            if(current().type == Token::Type::RParen){

                consume();

                return value;
            }

            while(true){

                value.arrayValues.push_back(parseValue());

                if(current().type == Token::Type::RParen) break;

                expect(Token::Type::Comma);
            }

            expect(Token::Type::RParen);

            return value;
        }

        if(current().type == Token::Type::Number){

            value.type = Value::Type::Number;
            value.numberValue = std::stod(current().text);

            consume();

            return value;
        }

        if(current().type == Token::Type::Identifier){

            value.type = Value::Type::Identifier;
            value.StringValue = current().text;

            consume();

            return value;
        }

        throw std::runtime_error("Invalid value");
    }

}