#pragma once
#include <string>

namespace Novella::Utils::String{

    std::string toUpper(const std::string& string);
    std::string toLower(const std::string& string);
    std::string trim(const std::string& string);
    std::string lTrim(const std::string& string);
    std::string rTrim(const std::string& string);
}