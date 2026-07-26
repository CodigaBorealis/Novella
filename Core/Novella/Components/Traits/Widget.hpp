#pragma once

#include "Layoutable.hpp"
#include "Renderable.hpp"
namespace Novella::Traits {

    struct Widget : public Layoutable, public Renderable{};
}