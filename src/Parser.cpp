#include "../Novella/Scene/Parser/Parser.hpp"
#include "../Novella/Scene/Parser/Lexer.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
//I hate this so much
namespace Novella::NScene::Parser{
    
    Parser::Parser(Lexer& lexer){

        while(true){

            Token token = lexer.next();

            tokens.push_back(token);

            if(token.type == Token::Type::EndOfFile) break;
        }
    }
    
    uint32_t Parser::getTypeID(const std::string& componentName) const{

        auto it = typeIDs.find(componentName);

        if(it == typeIDs.end()) throw std::runtime_error("Invalid component type: " + componentName);

        return it->second;
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

        if(current().text == "Resources"){

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

        object.objectType = getTypeID(current().text);

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
            
            if(current().text != "true" && current().text != "false") throw std::runtime_error("Boolean value can only be 'true' or 'false' at index: " + std::to_string(position));

            current().text == "true" ? value.data = true : value.data = false;

            consume();

            return value;
        }

        if(current().type == Token::Type::String){

            value.data = current().text;

            consume();

            return value;
        }

        if(current().type == Token::Type::LParen){
                        
            consume();
            
            if(current().type == Token::Type::RParen){

                consume();

                return value;
            }

            std::vector<Value> elements;

            while(true){

                if(current().type == Token::Type::LParen) throw std::runtime_error("Unsuported nested array at position " + std::to_string(position));

                elements.push_back(parseValue());

                if(current().type == Token::Type::RParen) break;

                expect(Token::Type::Comma);
            }

            expect(Token::Type::RParen);

            value.data = std::move(elements);

            return value;
        }

        if(current().type == Token::Type::Number){

            value.data = std::stod(current().text);

            consume();

            return value;
        }

        if(current().type == Token::Type::Identifier){

            value.isIdentifier = true;

            value.data = current().text;

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
