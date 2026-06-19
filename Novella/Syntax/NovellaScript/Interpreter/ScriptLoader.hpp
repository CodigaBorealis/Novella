#pragma once
#include <filesystem>
#include "../Lexer.hpp"
#include "../Parser.hpp"

namespace Novella::Syntax::NovellaScript{

    class ScriptLoader{

        public:

        static Script load(const std::filesystem::path& source);

    };

}