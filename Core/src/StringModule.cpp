#include "../Novella/Scripting/API/StringModule.hpp"
#include <cctype>
#include <cmath>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace Novella::NScript::Modules::String{


    std::string numberToString(Runtime::Context& context, double value){

        return std::to_string(value);
    }

    std::string boolToString(Runtime::Context& context, bool value){

        if(value) return "true";

        return "false";
    }

    bool isBool(Runtime::Context& context, const std::string& string){

        return string == "true" || string == "false";
    }

    bool isNumber(Runtime::Context &context, const std::string &string){

        if(string.empty()) return false;

        try{

            std::stod(string);

            return true;

        }catch(std::exception& e){

            return false;
        }
    }

    bool toBoolean(Runtime::Context& context, const std::string& string){

        if(string == "true") return true;

        if(string == "false") return false;

        throw std::runtime_error("NovellaScript Runtime Error: Can only convert 'true' or 'false' got: " + string);
    }

    double toNumber(Runtime::Context& context, const std::string& string){

        return std::stod(string);
    }

    double size(Runtime::Context& context, const std::string& string){

        return static_cast<double>(string.size());
    }    

    bool empty(Runtime::Context& context, const std::string& string){

        return string.empty();
    }

    std::string toUpper(Runtime::Context& context, const std::string& string){

        std::string copy = string;

        for(char& c : copy){

            c = std::toupper(static_cast<unsigned char>(c));
        }

        return copy;
    }

    std::string toLower(Runtime::Context& context, const std::string& string){

        std::string copy = string;

        for(char& c : copy){

            c = std::tolower(static_cast<unsigned char>(c));
        }

        return copy;      
    }    

    std::string capitalize(Runtime::Context& context, const std::string& string){

        if(string.empty()) return string;

        std::string copy = string;

        copy[0] = std::toupper(static_cast<unsigned char>(copy[0]));

        for(size_t x = 1; x < copy.size(); ++ x){

            copy[x] = std::tolower(static_cast<unsigned char>(copy[x]));
        }

        return copy;
    }

    bool contains(Runtime::Context& context, const std::string& string, const std::string& word){

        return string.contains(word);
    }    

    bool startsWith(Runtime::Context& context, const std::string& string, const std::string& word){

        return string.starts_with(word);
    }    

    bool endsWith(Runtime::Context& context, const std::string& string, const std::string& word){

        return string.ends_with(word);
    }        

    double indexOf(Runtime::Context& context, const std::string& string, const std::string& word){

        size_t index = string.find(word);

        if(index != std::string::npos) return static_cast<double>(index);

        return -1;
    }

    double lastIndexOf(Runtime::Context& context, const std::string& string, const std::string& word){

        size_t index = string.rfind(word);

        if(index != std::string::npos) return static_cast<double>(index);

        return -1;
    }

    std::string remove(Runtime::Context& context, const std::string& string, const std::string& word){

        if(string.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't remove anything from an empty string");

        if(word.empty()) return string;

        std::string copy = string;

        size_t pos = 0;

        while((pos = copy.find(word, pos)) != std::string::npos){

            copy.erase(pos, word.length());
        }

        return copy;
    }
    
    std::string replace(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement){

        if(string.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace anything from an empty string");

        if(search.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace an ocurrence without a target");

        std::string copy = string;

        size_t pos = 0;

        while((pos = copy.find(search, pos)) != std::string::npos){

            copy.replace(pos, search.length(), replacement);

            pos += replacement.length();
        }

        return copy;
    }

    std::string replaceFirst(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement){

        if(string.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace anything from an empty string");

        if(search.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace an ocurrence without a target");

        std::string copy = string;

        size_t pos = copy.find(search);

        if(pos != std::string::npos){

            copy.replace(pos, search.length(), replacement);
        }

        return copy;
    }

    std::string replaceLast(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement){

        if(string.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace anything from an empty string");

        if(search.empty()) throw std::runtime_error("NovellaScript Runtime Error: Can't replace an ocurrence without a target");

        std::string copy = string;

        size_t pos = copy.rfind(search);

        if(pos != std::string::npos){

            copy.replace(pos, search.length(), replacement);
        }

        return copy;
    }

    std::string trim(Runtime::Context& context, const std::string& string){

        return trimLeft(context, trimRight(context, string));
    }

    std::string trimLeft(Runtime::Context& context, const std::string& string){

        auto it = std::find_if_not(string.begin(), string.end(), [](unsigned char c){

            return std::isspace(c);
        });

        return std::string(it, string.end());
    }

    std::string trimRight(Runtime::Context& context, const std::string& string){

        auto it = std::find_if_not(string.rbegin(), string.rend(),[](unsigned char c){

            return std::isspace(c);
        }).base();

        return std::string(string.begin(), it);
    }

    std::string substringFrom(Runtime::Context& context, const std::string& string, double start){

        if(start < 0) throw std::runtime_error("NovellaScript Runtime Error: Can't create a substring from a negative index");

        if(start != std::floor(start)) throw std::runtime_error("NovellaScript Runtime Error: Can't create a substring from a decimal index");

        size_t star = static_cast<size_t>(start);

        if(star > string.size()) throw std::runtime_error("NovellaScript Runtime Error: Can't create a substring from index: " + std::to_string(star) + " string only has " + std::to_string(string.size()) + " characters");

        return string.substr(star);
    }

    std::string charAt(Runtime::Context& context, const std::string& string, double index){

        size_t idx = static_cast<size_t>(index);

        if(idx >= string.size()) throw std::runtime_error("NovellaScript Runtime Error: Can't access char at position :" + std::to_string(idx) + " string only has " + std::to_string(string.size()) + " characters");

        char c = string[idx];

        return std::string(1,c);
    }

    bool equalsIgnoreCase(Runtime::Context& context, const std::string& first, const std::string& second){

        if(first.length() != second.length()) return false;

        for(size_t x = 0; x < first.length(); x ++){

            if(std::toupper(static_cast<unsigned char>(first[x])) != std::toupper(static_cast<unsigned char>(second[x]))) return false;
        }

        return true;
    }

    std::string reverse(Runtime::Context& context, const std::string& string){

        if(string.empty()) return string;

        std::string copy = string;

        std::reverse(copy.begin(), copy.end());

        return copy;
    }
}