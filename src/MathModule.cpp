#include "../Novella/Scripting/API/MathModule.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace Novella::NScript::Modules::Math{

    double randomRange(Runtime::Context& context, double min, double max){

        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_real_distribution<double> dist(min,max);

        return dist(gen);
    }

    double clamp(Runtime::Context& context, double value, double min, double max){

        return std::clamp(value, min, max);
    }

    double squareRoot(Runtime::Context& context, double value){

        return std::sqrt(value);
    }

    double power(Runtime::Context& context, double value, double power){

        return std::pow(value, power);
    }
}