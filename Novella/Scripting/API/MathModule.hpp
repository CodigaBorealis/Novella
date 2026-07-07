#pragma once
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella::NScript::Modules::Math{

    double clamp(Runtime::Context& context, double value, double min, double max);

    double squareRoot(Runtime::Context& context, double value);

    double power(Runtime::Context& context, double value, double power);

    double abs(Runtime::Context& context, double value);

    double min(Runtime::Context& context, double a, double b);

    double max(Runtime::Context& context, double a, double b);

    double floor(Runtime::Context& context, double value);

    double ceil(Runtime::Context& context, double value);

    double round(Runtime::Context& context, double value);

    double sin(Runtime::Context& context, double value);

    double cos(Runtime::Context& context, double value);

    double tan(Runtime::Context& context, double value);

    double atan2(Runtime::Context& context, double a, double b);

    double degToRad(Runtime::Context& context, double value);
    
    double radToDeg(Runtime::Context& context, double value);

    double lerp(Runtime::Context& context, double a, double b, double t);

    double sign(Runtime::Context& context, double value);

}