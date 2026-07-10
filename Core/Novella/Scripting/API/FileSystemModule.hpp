#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella::NScript::Modules::FileSystem{

    bool isSafeName(const std::string& name);

    std::string createFile(Runtime::Context& context, const std::string& name, const std::string& contents);

    std::string removeFile(Runtime::Context& context, const std::string& name);

    std::string createFolder(Runtime::Context& context, const std::string& name);

    std::string removeFolder(Runtime::Context& context, const std::string& name);

    std::string moveFileToFolder(Runtime::Context& context, const std::string& fileName, const std::string& folderName);
}