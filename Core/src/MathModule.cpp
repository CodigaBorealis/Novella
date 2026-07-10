#include "../Novella/Scripting/API/MathModule.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <numbers>
#include <sys/types.h>

namespace Novella::NScript::Modules::Math{

    double clamp(Runtime::Context& context, double value, double min, double max){

        return std::clamp(value, min, max);
    }

    double squareRoot(Runtime::Context& context, double value){

        return std::sqrt(value);
    }

    double power(Runtime::Context& context, double value, double power){

        return std::pow(value, power);
    }

    double abs(Runtime::Context& context, double value){

        return std::abs(value);
    }

    double min(Runtime::Context& context, double a, double b){

        return std::min(a, b);
    }

    double max(Runtime::Context& context, double a, double b){

        return std::max(a, b);
    }

    double floor(Runtime::Context& context, double value){

        return std::floor(value);
    }

    double ceil(Runtime::Context& context, double value){

        return std::ceil(value);
    }

    double round(Runtime::Context& context, double value){

        return std::round(value);
    }

    double sin(Runtime::Context& context, double value){

        return std::sin(value);
    }

    double cos(Runtime::Context& context, double value){

        return std::cos(value);
    }

    double tan(Runtime::Context& context, double value){

        return std::tan(value);
    }

    double atan2(Runtime::Context& context, double a, double b){

        return std::atan2(a,b);
    }

    double degToRad(Runtime::Context& context, double value){

        return value * (std::numbers::pi / 180.0);
    }
    
    double radToDeg(Runtime::Context& context, double value){

        return value * (180.0 / std::numbers::pi);
    }

    double lerp(Runtime::Context& context, double a, double b, double t){

        return std::lerp(a, b, t);
    }

    double sign(Runtime::Context& context, double value){

        if(value > 0) return 1.0;

        if(value < 0) return -1.0;

        return 0.0;
    }

    double pi(Runtime::Context& context){

        return std::numbers::pi;
    }

    double e(Runtime::Context& context){

        return std::numbers::e;
    }

    double phi(Runtime::Context& context){

        return std::numbers::phi;
    }

    double sqrt2(Runtime::Context& context){

        return std::numbers::sqrt2;
    }

    double sqrt3(Runtime::Context& context){

        return std::numbers::sqrt3;
    }

    double invPi(Runtime::Context& context){

        return std::numbers::inv_pi;
    }

    double invSqrtPi(Runtime::Context& context){

        return std::numbers::inv_sqrtpi;
    }

    double ln2(Runtime::Context& context){

        return std::numbers::ln2;
    }

    double ln10(Runtime::Context& context){

        return std::numbers::ln10;
    }

    double log2e(Runtime::Context& context){

        return std::numbers::log2e;
    }

    double log10e(Runtime::Context& context){

        return std::numbers::log10e;
    }

    double egamma(Runtime::Context& context){

        return std::numbers::egamma;
    }
}