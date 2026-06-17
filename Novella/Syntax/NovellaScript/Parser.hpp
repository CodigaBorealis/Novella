#pragma once
#include "Script.hpp"
#include "Token.hpp"
#include <cstddef>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    class Lexer;

    struct SceneDefinition;

    struct ObjectDefinition;

    struct Property;

    struct Value;

    class Parser{

        public:
        
        explicit Parser(Lexer& lexer);

        SceneDefinition parse();

        private:
        
        std::vector<Token> tokens;
        size_t position = 0;
        
        Token& current();
        Token& peek(size_t offset);

        void consume();
        void expect(Token::Type type);

        void parseResources(SceneDefinition& scene);
        void parseInput(SceneDefinition& scene);

        SceneDefinition parseScene();
        ObjectDefinition parseObject();
        Property parseProperty();
        Value parseValue();
    };

}