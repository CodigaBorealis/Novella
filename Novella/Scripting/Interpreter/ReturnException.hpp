#pragma once
#include "../Parser/Expression.hpp"
#include <exception>
namespace Novella::NScript::Runtime{

    class ReturnException : public std::exception{

        public:

        Parser::Value value;

        explicit ReturnException(Parser::Value value)
            :
            value(value)
            {}

        const char* what() const noexcept override{

            return "NovellaScript Control Flow: return";
        }
    };
}