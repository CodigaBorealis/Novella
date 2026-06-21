#pragma once
#include <cstddef>
#include <string_view>

namespace Novella::NScene::Parser{

    struct Token;

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