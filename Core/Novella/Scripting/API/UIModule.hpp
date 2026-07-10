#pragma once
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella::NScript::Modules::UI{

    void createLabel(Runtime::Context&);

    void createButton(Runtime::Context&);

    void createSprite(Runtime::Context&);
}