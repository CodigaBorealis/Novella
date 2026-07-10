#include "../Novella/Utils/String.hpp"
#include <cctype>
#include <algorithm>

namespace Novella::Utils::String{

    std::string toUpper(const std::string& string){

        std::string copy = string;

        for(char& c : copy){

            c = std::toupper(static_cast<unsigned char>(c));
        }

        return copy;
    }

    std::string toLower(const std::string& string){

        std::string copy = string;
        
        for(char& c : copy){

            c = std::tolower(static_cast<unsigned char>(c));
        }

        return copy;
    }

    std::string trim(const std::string& string){

        return lTrim(rTrim(string));
    }

    std::string lTrim(const std::string& string){

        std::string copy = string;

        auto it = std::find_if_not(string.begin(), string.end(), [](unsigned char c){

            return std::isspace(c);
        });
        
        copy = std::string(it, string.end());

        return copy;
    }

    std::string rTrim(const std::string& string){

        std::string copy = string;
        
        auto it = std::find_if_not(string.rbegin(), string.rend(),[](unsigned char c){

            return std::isspace(c);
        }).base();

        copy = std::string(string.begin(), it);

        return copy;

    }

}