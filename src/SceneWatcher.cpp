#include "../Novella/Scene/SceneWatcher.hpp"
#include <filesystem>

namespace Novella {
    
    bool SceneWatcher::hasFileChanged(){

        auto currentTime = std::filesystem::last_write_time(sceneFile);

        if(currentTime != lastWriteTime){

            lastWriteTime = currentTime;

            return true;
        }

        return false;
    }

    const std::filesystem::path& SceneWatcher::getSceneFile() const{

        return this->sceneFile;
    }

    void SceneWatcher::setSceneFile(const std::filesystem::path& file){

        sceneFile = file;
    }

}