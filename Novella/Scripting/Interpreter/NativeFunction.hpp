#pragma once

#include <functional>
#include <vector>
#include "../Parser/Expression.hpp"

namespace Novella::NScript::Runtime{

    using NativeFunction = std::function<Parser::Value(const std::vector<Parser::Value>&)>;
}