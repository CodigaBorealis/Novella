#pragma once
#include <cstddef>
#include <string_view>
#include <unordered_map>
#include "Token.hpp"

namespace Novella::NScript::Parser{
    
    static const std::unordered_map<std::string, Token::Type> keywords = {

        {"if", Token::Type::If},
        {"else", Token::Type::Else},
        {"var", Token::Type::Var},
        {"fn", Token::Type::Define},
        {"return", Token::Type::Return},
        {"true", Token::Type::Boolean},
        {"false", Token::Type::Boolean},
        {"then", Token::Type::Then},
        {"endIf", Token::Type::EndIf},
        {"endFunction", Token::Type::EndFunction},
        {"and", Token::Type::And},
        {"or", Token::Type::Or},
        {"not", Token::Type::Not},
        {"is", Token::Type::Equals}

    };

    class Lexer{

        public:
        
        explicit Lexer(std::string_view source)
            :
            source(source)
            {}

        Token next();

        Token identifier();

        Token number();

        Token string();
        
        private:
        
        char peek();
        char advance();

        bool eof() const;

        void skipWhitespace();

        std::string_view source;
        size_t currentCharacter = 0;
        size_t line = 1;
        size_t column = 1;

    };

}