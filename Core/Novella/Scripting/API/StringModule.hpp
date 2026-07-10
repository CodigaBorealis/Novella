#pragma once
#include "../Interpreter/RuntimeContext.hpp"
#include <vector>

namespace Novella::NScript::Modules::String{

    std::string numberToString(Runtime::Context& context, double value);

    std::string boolToString(Runtime::Context& context, bool value);

    bool isNumber(Runtime::Context& context, const std::string& string);

    bool isBool(Runtime::Context& context, const std::string& string);

    bool toBoolean(Runtime::Context& context, const std::string& string);

    double toNumber(Runtime::Context& context, const std::string& string);

    double size(Runtime::Context& context, const std::string& string);    

    bool empty(Runtime::Context& context, const std::string& string);

    std::string toUpper(Runtime::Context& context, const std::string& string);

    std::string toLower(Runtime::Context& context, const std::string& string);    

    std::string capitalize(Runtime::Context& context, const std::string& string);

    bool contains(Runtime::Context& context, const std::string& string, const std::string& word);    

    bool startsWith(Runtime::Context& context, const std::string& string, const std::string& word);    

    bool endsWith(Runtime::Context& context, const std::string& string, const std::string& word);        

    double indexOf(Runtime::Context& context, const std::string& string, const std::string& word);

    double lastIndexOf(Runtime::Context& context, const std::string& string, const std::string& word);

    std::string remove(Runtime::Context& context, const std::string& string, const std::string& word);

    std::string replace(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement);

    std::string replaceFirst(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement);

    std::string replaceLast(Runtime::Context& context, const std::string& string, const std::string& search, const std::string& replacement);

    std::string trim(Runtime::Context& context, const std::string& string);

    std::string trimLeft(Runtime::Context& context, const std::string& string);

    std::string trimRight(Runtime::Context& context, const std::string& string);

    std::string substringFrom(Runtime::Context& context, const std::string& string, double start);

    std::string left(Runtime::Context& context, const std::string& string, double count);

    std::string right(Runtime::Context& context, const std::string& string, double count);

    std::string charAt(Runtime::Context& context, const std::string& string, double index);

    bool equalsIgnoreCase(Runtime::Context& context, const std::string& first, const std::string& second);

    std::string reverse(Runtime::Context& context, const std::string& string);
}