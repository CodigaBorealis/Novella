#include "../Novella/Scripting/API/RandomModule.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <stdexcept>

namespace Novella::NScript::Modules::Random{

    double randomInt(Runtime::Context& context, double min, double max){

        if(!std::isfinite(min) || std::floor(min) != min) throw std::runtime_error("NovellaScript Runtime Error: Generating a random integer in a range requires two finite integers");
        
        if(!std::isfinite(max) || std::floor(max) != max) throw std::runtime_error("NovellaScript Runtime Error: Generating a random integer in a range requires two finite integers");

        int64_t iMin = static_cast<int64_t>(min);
        int64_t iMax = static_cast<int64_t>(max);

        if(iMin > iMax) throw std::runtime_error("NovellaScript Runtime Error: Generating a random integer in a range requires min to be < than max");

        if(iMin < std::numeric_limits<int64_t>::min() || iMax > std::numeric_limits<int64_t>::max()) throw std::runtime_error("NovellaScript Runtime Error: Integer range exceeds int64_t range");

        std::uniform_int_distribution<int64_t> dist(min, max);

        return static_cast<double>(dist(rng));
    }

    double randomFloat(Runtime::Context& context, double min, double max){

        if(!std::isfinite(min)) throw std::runtime_error("Generating a random float requires two finite floating numbers");

        if(!std::isfinite(max)) throw std::runtime_error("Generating a random float requires two finite floating numbers");

        if(min > max) throw std::runtime_error("NovellaScript Runtime Error: Generating a random float requires min to be < than max");

        std::uniform_real_distribution<double> dist(min, max);

        return dist(rng);
    }

    bool randomBool(Runtime::Context& context){

        std::bernoulli_distribution dist(0.5);

        return dist(rng);
    }

    std::string randomString(Runtime::Context& context, const std::string& characterPool, double length){
        
        if(!std::isfinite(length) || std::floor(length) != length) throw std::runtime_error("NovellaScript Runtime Error: Generating a random string requires length to be a finite integer");

        if(length < 0) throw std::runtime_error("NovellaScript Runtime Error: length of a random string cannot be negative");

        size_t size = static_cast<size_t>(length);

        if(characterPool.empty()) throw std::runtime_error("NovellaScript Runtime Error: Character pool cannot be empty when generating a random string");

        std::string randomString{};

        randomString.reserve(size);

        std::uniform_int_distribution<size_t> dist(0, characterPool.size() - 1);

        for(size_t x = 0; x < size; x ++){

            randomString += characterPool[dist(rng)];
        }

        return randomString;
    }

}