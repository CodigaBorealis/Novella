#include "../Novella/Scripting/API/FileSystemModule.hpp"
#include "../Novella/Scripting/API/StringModule.hpp"
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <system_error>
#ifdef _WIN32
#include <array>
#include <algorithm>
#include <cctype>
#endif

namespace Novella::NScript::Modules::FileSystem{

    bool isSafeName(const std::string& name){

        if(name.empty()) return false;

        #ifdef _WIN32

        std::string upperName = name;

        std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](unsigned char c){
            
            return static_cast<char>(std::toupper(c));
        });

        static const std::array<std::string, 22> reservedWindowsNames{"CON","PRN","AUX","NUL","COM1", "COM2", "COM3",
            "COM4", "COM5", "COM6", "COM7", "COM8", "COM9","LPT1", "LPT2", "LPT3", "LPT4", "LPT5",
            "LPT6", "LPT7", "LPT8", "LPT9"};
        
        if(std::find(reservedWindowsNames.begin(), reservedWindowsNames.end(), upperName) != reservedWindowsNames.end()) return false;
        #endif

        return true;
    }

    std::filesystem::path createSecurePath(const std::filesystem::path& root, const std::filesystem::path& userInput){

        std::filesystem::path combined = root / userInput;

        std::error_code ec;

        std::filesystem::path truePath = std::filesystem::weakly_canonical(combined, ec);

        if(ec) return {};

        auto[rootEnd, pos] = std::mismatch(root.begin(), root.end(), truePath.begin());

        if(rootEnd != root.end()) throw std::runtime_error("NovellaScript Runtime Error: Access denied path escapes sandbox boundary via symlink or traversal");

        return truePath;
    }

    std::string createFile(Runtime::Context& context, const std::string& name, const std::string& contents){
        
        if(!isSafeName(name))  return "Rejected unsafe filename '" + name + "'";

        std::filesystem::path resolved = createSecurePath(context.projectRoot, {name});

        if(std::filesystem::exists(resolved)) return "File could not be created because a file with this name already exists '" + name;

        std::ofstream file(resolved);
        
        if(file.is_open()){

            file << contents;

            file.close();
            
            return "File created at " + resolved.string();
        }

        return "File could not be written '" + name;

    }

    std::string removeFile(Runtime::Context& context, const std::string& name){
        
        if(!isSafeName(name)) return "Rejected unsafe filename '" + name + "'";

        std::filesystem::path resolved = createSecurePath(context.projectRoot, name);

        if(!std::filesystem::exists(resolved)) return "File not found: '" + name;

        if(std::filesystem::remove(resolved)) return "File has been deleted '" + name;

        return "File could not be deleted '" + name +"'";
    }

    std::string createFolder(Runtime::Context& context, const std::string& name){
        
        if(!isSafeName(name)) return "Rejected unsafe filename '" + name + "'";

        std::filesystem::path resolved = createSecurePath(context.projectRoot, name);

        if(std::filesystem::exists(resolved)) return "Folder could not be created because a folder with this name already exists '" + name;

        if(std::filesystem::create_directories(resolved)) return "Folder has been created '" + name +"'";

        return "Folder could not be created '"+ name + "'";
    }

    std::string removeFolder(Runtime::Context& context, const std::string& name){
        
        if(!isSafeName(name)) return "Rejected unsafe filename '" + name + "'";

        std::filesystem::path resolved = createSecurePath(context.projectRoot, {name});

        if(!std::filesystem::exists(resolved)) return "Folder not found: '" + name + "'";

        if(std::filesystem::remove_all(resolved)) return "Folder has been deleted '" + name + "'";

        return "Folder could not be deleted '" + name + "'";
    }

    std::string moveFileToFolder(Runtime::Context& context, const std::string& fileName, const std::string& folderName){
        
        if(!isSafeName(fileName)) return "rejected unsafe filename '" + fileName + "'";
        if(!isSafeName(folderName)) return "rejected unsafe folderName '" + folderName + "'";

        std::filesystem::path source = createSecurePath(context.projectRoot , fileName);
        if(!std::filesystem::exists(source)) return "Source file does not exist '" + source.string() +"'";

        std::filesystem::path destinationFolder = createSecurePath(context.projectRoot , folderName);
        if(!std::filesystem::is_directory(destinationFolder)) return "Destination folder does not exist: " + destinationFolder.string();

        std::filesystem::path relativeDestination = std::filesystem::path(folderName) / fileName;
    
        std::filesystem::path destination = createSecurePath(context.projectRoot, relativeDestination);
        if(std::filesystem::exists(destination)) return "Destination file already exists '" + destination.string() + "'";

        std::error_code ec;

        std::filesystem::rename(source, destination, ec);

        if(ec) return "File could not be moved '" + fileName + "'";
        
        return "File moved sucessfully from '" + source.string() + "' to '" + destination.string() + "'";

    }

}