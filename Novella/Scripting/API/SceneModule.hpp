#pragma once
#include <cstdint>
#include <string>
#include "../../Core/Math/Vector2x.hpp"

namespace Novella{

    class SceneManager;
}

namespace Novella::NScript{

    class SceneModule{

        public:
        
            SceneModule() = delete;

            SceneModule(SceneManager& sceneManager)
                :
                sceneManager(sceneManager)
                {}

            uint64_t getHandle(const std::string& name);

            void destroy(uint64_t handle);

            void setPosition(uint64_t handle, Vector2d& position);

        private:

        SceneManager& sceneManager;

    };   
}