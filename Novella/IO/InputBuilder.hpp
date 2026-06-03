#pragma once
#include <string>

namespace Novella::Syntax::Scene {

    struct InputBindingDefinition;
}

namespace Novella::Input::Mouse{

    enum class Button;

}

namespace Novella::Input::Keyboard{

    enum class Key;


}
namespace Novella{
    
    class Engine;
}

namespace Novella::SceneLoader{

    class InputBuilder{

        public:

            static void buildInput(Engine& engine, const Syntax::Scene::InputBindingDefinition& input);

        private:

        static Input::Mouse::Button getMouseButton(const std::string& button);
        static Input::Keyboard::Key getKeyboardKey(const std::string& key);

    };

}