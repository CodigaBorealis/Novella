#pragma once
#include "Token.hpp"
#include <cstddef>
#include <vector>
#include "ScriptFwd.hpp"
#include "Definition.hpp"

namespace Novella::NScript::Parser{

    class Lexer;

    struct Script;

    struct Value;

    class Parser{

        public:
        
        explicit Parser(Lexer& lexer);

        Script parse();

        private:

        std::vector<Token> tokens;
        size_t position = 0;
        
        Token& current();
        Token& peek(size_t offset);

        void consume();

        void expect(Token::Type type);

        void Parse(Script& scene);

        Script parseScript();
        Statement parseStatement();
        ExpressionStatement parseExpressionStatement();
        ReturnStatement parseReturn();
        IfStatement parseIf();
        VariableStatement parseVariable();

        FunctionDefinition parseFunctionDefinition();

        Expression parseAssignment();
        Expression parsePrimary();
        Expression parseUnary();
        Expression parseFactor();
        Expression parseTerm();
        Expression parseComparison();
        Expression parseEquality();
        Expression parseLogicalAnd();
        Expression parseLogicalOr();
        Expression parseExpression();
        Expression parseArrayExpression();
        Expression parsePostFix();
    };

}