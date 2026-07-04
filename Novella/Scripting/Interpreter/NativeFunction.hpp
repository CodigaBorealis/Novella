#pragma once

#include <functional>
#include <vector>
#include "../Parser/Expression.hpp"
#include "RuntimeContext.hpp"

namespace Novella::NScript::Runtime{

    using NativeFunction = std::function<Parser::Value(Runtime::Context& context, const std::vector<Parser::Value>&)>;
}