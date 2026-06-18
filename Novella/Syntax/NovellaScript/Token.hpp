#pragma once
#include <string>
namespace Novella::Syntax::NovellaScript{

    struct Token{

        Token() = delete;

        enum class Type : int{

            Identifier,
            String,
            Character,
            Number,
            Boolean,

            If,
            Else,
            Var,
            Const,
            Persistent,
            Module,
            Import,
            Export,
            Define,
            Return,
            OnFirstLoad,
            From,
            As,

            Assign,
            Equals,
            NotEquals,

            Less,
            Greater,
            LessEquals,
            GreaterEquals,

            Plus,

            Minus,

            Multiply,

            Divide,

            Modulo,

            Increment,
            Decrement,

            And,
            Or,
            Not,

            LBrace,
            RBrace,

            LParen,
            RParen,

            LBracket,
            RBracket,

            Comma,
            SemiColon,
            Dot,

            EndOfFile
        };

        Token(Type type, const std::string& text)
            :
            type(type),
            text(text)
            {}

        Type type;

        std::string text;
    };

}