#pragma once
#include <cstdint>
#include <string>
#include "../../../Math/Vector2x.hpp"

namespace Novella{

    class SceneManager;
}

namespace Novella::Syntax::NovellaScript::API{

    class SceneModule{

        public:
        
            SceneModule() = delete;

            SceneModule(SceneManager& sceneManager)
                :
                sceneManager(sceneManager)
                {}

            uint64_t getObject(const std::string& name);

            void destroy(uint64_t handle);

            void setPosition(uint64_t handle, Novella::Math::Vector2d& position);

        private:

        SceneManager& sceneManager;

    };   
}