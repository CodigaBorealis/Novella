#pragma once
#include "EngineConfig.hpp"

namespace Novella::Project{

    EngineConfig load(const std::filesystem::path& configFile);

}