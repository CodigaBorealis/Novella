#pragma once
#include <filesystem>

namespace Novella::NScript::Parser{

    struct Script;
};

namespace Novella::NScript::Runtime{

    class ScriptLoader{

        public:

        static Parser::Script load(const std::filesystem::path& source);

    };

}