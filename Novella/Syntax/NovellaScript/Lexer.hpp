#pragma once
#include <cstddef>
#include <string_view>
#include <unordered_map>
#include "Token.hpp"

namespace Novella::Syntax::NovellaScript{
    
    static const std::unordered_map<std::string, Token::Type> keywords = {

        {"if", Token::Type::If},
        {"else", Token::Type::Else},
        {"var", Token::Type::Var},
        {"const", Token::Type::Const},
        {"persistent", Token::Type::Persistent},
        {"as", Token::Type::As},
        {"exec_once", Token::Type::OnFirstLoad},
        {"define", Token::Type::Define},
        {"return", Token::Type::Return},
        {"module", Token::Type::Module},
        {"import", Token::Type::Import},
        {"export", Token::Type::Export},
        {"true", Token::Type::Boolean},
        {"false", Token::Type::Boolean}

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
        
        Token character();

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