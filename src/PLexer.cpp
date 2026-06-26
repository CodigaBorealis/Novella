#include "../Novella/Project/Lexer.hpp"
#include "../Novella/Project/Token.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

namespace Novella::Project{

Token Lexer::next(){

        skipWhitespace();

        if(eof()) return {Token::Type::EndOfFile, ""};

        char c = peek();

        if(c == '-' && currentCharacter + 1 < source.size() && std::isdigit(static_cast<unsigned char>(source[currentCharacter + 1]))) return  number();

        switch(c){

            case '=':

                advance();
                
                return {Token::Type::Equals, "="};

            case '{':

                advance();

                return {Token::Type::LBrace, "{"};

            case '}':

                advance();
                
                return {Token::Type::RBrace, "}"};

            case '"':

                return string();
        }

        if(std::isdigit(static_cast<unsigned char>(c))) return number();

        if(std::isalpha(static_cast<unsigned char>(c)) || c == '_') return identifier();

        std::cout << "SOURCE: " << source << "\n";

        char received = source.at(currentCharacter);

        unsigned char casted = static_cast<unsigned char>(received);

        std::cout << "RECEIVED: \n";

        std::cout << received;

        std::cout << "\n";

        std::cout << "CASTED\n";
        
        std::cout << casted;

        std::cout << "\n";
        throw std::runtime_error(std::string("PLEXER: Unexpected character '" ) + c + "' at : " + std::to_string(line) + ":" + std::to_string(column));

    }

    Token Lexer::identifier(){

        std::string value;

        while(!eof()){

            char c = peek();

            if(std::isalnum(static_cast<unsigned char>(c)) || c == '_'){

                value += advance();

            }else{

                break;
            }
        }

        return {Token::Type::Identifier, value};
    }

    Token Lexer::number(){

        std::string value;

        if(peek() == '-') throw std::runtime_error("Invalid '-' token at " + std::to_string(line) + ":" + std::to_string(column));

        while(!eof()){

            char c = peek();

            if(std::isdigit(static_cast<unsigned char>(c))){
                
                value += advance();

            }else{

                break;
            }
        }
        
        if(!value.empty() && value.back() == '.') throw std::runtime_error("Malformed integer literal at " + std::to_string(line) + ":" + std::to_string(column));
        
        if(!eof()){

            char trailing = peek();
            
            if(trailing == '-' || trailing == '.') throw std::runtime_error("Malformed integer literal at " + std::to_string(line) + ":" + std::to_string(column));
        }

        if(value.empty()) throw std::runtime_error("Expected a value at " + std::to_string(line) + std::to_string(column));

        return{Token::Type::Number, value};
    }

    Token Lexer::string(){

        advance();

        std::string value;

        while(!eof() && peek() != '"'){

            value += advance();
        }

        if(eof()) throw std::runtime_error("Unterminated string literal at " + std::to_string(line) + ":" + std::to_string(column));

        if(peek() == '"') advance();

        return{Token::Type::String, value};
    }

    char Lexer::peek(){

        if(eof()) return '\0';

        return source[currentCharacter];
    };

    char Lexer::advance(){

        if(eof()) return '\0';

        char current = source[currentCharacter];

        if(current == '\n'){

            line ++;

            column = 1;

        }else{

            column ++;

        }

        currentCharacter++;

        return current;
    };

    bool Lexer::eof() const{

        return currentCharacter >= source.size();
    }

    void Lexer::skipWhitespace(){

        while(!eof()){

            char c = peek();

            if(c == ' ' || c == '\t' || c == '\n' || c =='\r'){

                advance();

            }else if(c == '#'){

                while(!eof() && peek() != '\n' && peek() != '\r'){

                    advance();
                }
                
            }else{

                break;
            }
        }
    }
}