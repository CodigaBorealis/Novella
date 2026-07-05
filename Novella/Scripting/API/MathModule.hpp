#pragma once
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella::NScript::Modules::Math{

    double randomRange(Runtime::Context& context, double min, double max);

    double clamp(Runtime::Context& context, double value, double min, double max);

    double squareRoot(Runtime::Context& context, double value);

    double power(Runtime::Context& context, double value, double power);
}