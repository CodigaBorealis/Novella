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

        if(current().type != type) throw std::runtime_error("Unexpected token: " + current().text + " at position " + std::to_string(position) );

        consume();
    }

    SceneDefinition Parser::parse(){

        return parseScene();
    }

    void Parser::registerSeenSection(const std::string& section){

        auto& registry = parseRegistry.at(ParseRegistry::stringToSection(section));

        if(registry.firstDefinitionIndex == -1) registry.firstDefinitionIndex = position;//Is off by a lot but i will fix it later

        registry.evalCount ++;
    }

    SceneDefinition Parser::parseScene(){

        SceneDefinition scene{};

        while(current().type != Token::Type::EndOfFile){

        if(current().text == "Window"){
            
            registerSeenSection(current().text);

            parseWindow(scene);

        }else if(current().text == "Resources"){

            registerSeenSection(current().text);

            parseResources(scene); 

        }else if(current().text == "Components"){
            
            registerSeenSection(current().text);

            parseComponents(scene);

        }else if(current().text == "Scripts"){
            
            registerSeenSection(current().text);

            parseScripts(scene);

        }else{

            throw std::runtime_error("Unexpected section: " + current().text + " at position: "+ std::to_string(position));
        }
        
        }

        checkIntegrity(parseRegistry);

        return scene;

    }
    
    void Parser::parseWindow(SceneDefinition& scene){
        
        expect(Token::Type::Identifier);

        expect(Token::Type::LBrace);
        
        while(current().type != Token::Type::RBrace){
            
            scene.windowProperties.push_back(parseProperty());
        }

        expect(Token::Type::RBrace);

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

            if(position == startPosition) throw std::runtime_error("Parser error: Stalled at token '" + current().text + "' position " + std::to_string(position));

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

        if(current().type == Token::Type::Boolean){

            value.type = Value::Type::Boolean;
            
            if(current().text != "true" && current().text != "false") throw std::runtime_error("Boolean value can only be 'true' or 'false' at index: " + std::to_string(position));

            current().text == "true" ? value.boolValue = true : value.boolValue = false;

            consume();

            return value;
        }

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

                if(current().type == Token::Type::LParen) throw std::runtime_error("Unsuported nested array at position " + std::to_string(position));

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

    void Parser::parseComponents(SceneDefinition& scene){
        
        expect(Token::Type::Identifier);

        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            scene.objects.push_back(parseObject());

        }

        expect(Token::Type::RBrace);
    }
    
    void Parser::parseScripts(SceneDefinition& scene){

        expect(Token::Type::Identifier);
        
        expect(Token::Type::LBrace);

        while(current().type != Token::Type::RBrace){

            ScriptDefinition script{};

            script.name = current().text;

            expect(Token::Type::Identifier);

            expect(Token::Type::Equals);

            script.path = current().text;

            expect(Token::Type::String);

            scene.scripts.push_back(script);
        }

        expect(Token::Type::RBrace);
    }

    void Parser::checkIntegrity(const std::unordered_map<Section, ParseRegistry>& parseRegistry){

        for(const auto& [section, value]: parseRegistry){

            auto& registry = parseRegistry.at(section);

            if(registry.evalCount > 1) throw std::runtime_error("Redefinition for section '" + ParseRegistry::sectionToString(section) +"' previous definition at index: " + std::to_string(registry.firstDefinitionIndex));
            
            if(!registry.optional && registry.evalCount == 0) throw std::runtime_error("Missing neccesary section '" + ParseRegistry::sectionToString(section) + "'");

        }
        
    }
}
