#pragma once
#include <filesystem>

namespace Novella{

    class SceneWatcher{

        public:

        SceneWatcher() = default;

        bool hasFileChanged();

        const std::filesystem::path& getSceneFile() const;

        void setSceneFile(const std::filesystem::path& file);

        private:

        std::filesystem::path sceneFile;
        std::filesystem::file_time_type lastWriteTime;
    };

}