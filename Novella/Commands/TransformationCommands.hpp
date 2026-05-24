#pragma once
#include "CommandContext.hpp"
namespace Novella::Commands{

    void resize(Scene& scene, Attribute::Object& object, const nlohmann::json& args);

    void move(Scene& scene, Attribute::Object& object, const nlohmann::json& args);

    void setPosition(Scene& scene, Attribute::Object& object, const nlohmann::json& args);

    void setColor(Scene& scene, Attribute::Object& object, const nlohmann::json& args);

    void setTransparency(Scene& scene, Attribute::Object& object, const nlohmann::json &args);

    void setText(Scene& scene, Attribute::Object& object, const nlohmann::json &args);
}