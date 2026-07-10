#pragma once
#include <random>
#include <string>
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella::NScript::Modules::Random{

    inline std::mt19937 rng;

    double randomInt(Runtime::Context& context, double min, double max);

    double randomFloat(Runtime::Context& context, double min, double max);

    bool randomBool(Runtime::Context& context);

    std::string randomString(Runtime::Context& context, const std::string& characterPool, double length);

}