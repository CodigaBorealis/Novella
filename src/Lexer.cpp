#include "../Novella/Syntax/Scene/Lexer.hpp"
#include "../Novella/Syntax/Scene/Token.hpp"
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

namespace Novella::Syntax::Scene{

    Token Lexer::next(){

        skipWhitespace();

        if(eof()) return {Token::Type::EndOfFile, ""};

        char c = peek();

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

            case '(':

                advance();

                return {Token::Type::LParen, "("};

            case ')':

                advance();

                return {Token::Type::RParen, ")"};

            case ',':

                advance();

                return {Token::Type::Comma, ","};

            case '"':

                return string();
        }

        if(std::isdigit(c)) return number();

        if(c == '-' && currentCharacter + 1 < source.size() && std::isdigit(source[currentCharacter + 1])) return  number();

        if(std::isalpha(c) || c == '_') return identifier();
                
        throw std::runtime_error(std::string("Unexpected character '" ) + c + "' at : " + std::to_string(line) + ":" + std::to_string(column));
    }
    Token Lexer::identifier(){

        std::string value;

        while(!eof()){

            char c = peek();

            if(std::isalnum(c) || c == '_'){

                value += advance();

            }else{

                break;
            }
        }

        return {Token::Type::Identifier, value};
    }

    Token Lexer::number(){

        short dotCount = 0;
        std::string value;

        if(peek() == '-') value += advance();

        while(!eof()){

            char c = peek();

            if(std::isdigit(c) || c == '.'){
                
                value += advance();

                if(c == '.'){
                    
                    dotCount ++;

                    if(dotCount > 1) throw std::runtime_error(std::string("Repeated '.' character +  at : " + std::to_string(line) + ":" + std::to_string(column)));
                    
                    char nextChar = peek();

                    if(nextChar == '-' || nextChar == '.') throw std::runtime_error("Malformed number literal at " + std::to_string(line) + ":" + std::to_string(column));

                }

            }else{

                break;
            }
        }
        
        if(!value.empty() && value.back() == '.') throw std::runtime_error("Malformed number literal at " + std::to_string(line) + ":" + std::to_string(column));
        
        if(!eof()){

            char trailing = peek();
            
            if(trailing == '-' || trailing == '.') throw std::runtime_error("Malformed number literal at " + std::to_string(line) + ":" + std::to_string(column));
        }

        return{Token::Type::Number, value};
    }

    Token Lexer::string(){

        advance();

        std::string value;

        while(!eof() && peek() != '"'){

            value += advance();
        }

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