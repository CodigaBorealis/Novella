#pragma once
#include <nlohmann/json_fwd.hpp>

namespace Novella::Commands{

    void setWindowTitle(const nlohmann::json &args);

    void setWindowIcon(const nlohmann::json &args);

    void setWindowPosition(const nlohmann::json &args);

    void setWindowSize(const nlohmann::json &args);

    void closeWindow();

}