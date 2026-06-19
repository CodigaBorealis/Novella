#include "../Novella/Syntax/NovellaScript/Lexer.hpp"
#include "../Novella/Syntax/NovellaScript/Token.hpp"
#include <stdexcept>
#include <string>
#include <string_view>

namespace Novella::Syntax::NovellaScript{

    Token Lexer::next(){

        skipWhitespace();

        if(eof()) return {Token::Type::EndOfFile, ""};

        char c = peek();

        if(c == '-' && currentCharacter + 1 < source.size() && std::isdigit(source[currentCharacter + 1])) return  number();

        switch(c){

            case '=':

                advance();
                
                if(peek() == '='){

                    advance();

                    return {Token::Type::Equals, "=="};
                }

                return {Token::Type::Assign, "="};
            
            case '!':

                advance();

                if(peek() == '='){

                    advance();

                    return {Token::Type::NotEquals, "!="};
                }

                return {Token::Type::Not, "!"};
            
            case '<':

                advance();

                if(peek() == '='){

                    advance();

                    return {Token::Type::LessEquals, "<="};
                }

                return {Token::Type::Less, "<"};

            case '>':

                advance();

                if(peek() == '='){

                    advance();

                    return {Token::Type::GreaterEquals, ">="};
                }

                return {Token::Type::Greater, ">"};
            
            case '+':

                advance();

                if(peek() == '+'){

                    advance();

                    return {Token::Type::Increment, "++"};
                }

                return {Token::Type::Plus, "+"};
            
            case '-':

                advance();

                if(peek() == '-'){

                    advance();

                    return {Token::Type::Decrement, "--"};
                }

                return {Token::Type::Minus, "-"};

            case '*':

                advance();

                return {Token::Type::Multiply, "*"};

            case '/':

                advance();

                return {Token::Type::Divide, "/"};
            
            case '%':

                advance();

                return {Token::Type::Modulo, "%"};

            case '&':

                advance();
                
                if(peek() == '&'){

                    advance();

                    return {Token::Type::And, "&&"};
                }

                throw std::runtime_error("Expected a second '&' token at: " + std::to_string(line) + ":" + std::to_string(column));

            case '|':

                advance();

                if(peek() ==  '|'){

                    advance();
                    
                    return {Token::Type::Or, "||"};
                }

                throw std::runtime_error("Expected a second '|' token at: " + std::to_string(line) + ":" + std::to_string(column));

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

            case ';':

                advance();

                return {Token::Type::SemiColon, ";"};

            case '.':

                advance();

                return{Token::Type::Dot, "."};

            case '[':

                advance();

                return {Token::Type::LBracket, "["};

            case ']':

                advance();

                return {Token::Type::RBracket, "]"};

            case '"':

                return string();
                
            case '\'':

                return character();
        }

        if(std::isdigit(c)) return number();

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

        auto it = keywords.find(value);

        if(it != keywords.end()){

            return {it->second, value};
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

    Token Lexer::character(){

        advance();

        if(eof()) throw std::runtime_error("Undetermined character literal at " + std::to_string(line) + ":" + std::to_string(column));

        char c = advance();

        if(peek() != '\'') throw std::runtime_error("Expected closing quote at " + std::to_string(line) + ":" + std::to_string(column));

        advance();

        return {Token::Type::Character, std::string(1, c)};
    }
}