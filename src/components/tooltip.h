#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "lable": "Tooltip", 
        "content": "{content}"
        "trigger": {}
    }
    */
    bool Tooltip(
        const nlohmann::json& attr, 
        std::function<bool(const nlohmann::json&)> trigger
    );

    void ShowTooltipExamples();
}