#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "{label}",
        "variant": "primary|secondary|destructive|outline", 
        "icon": "{icon}",
        "shape": "circle|rectangle"
    }
    */
    bool Badge(const nlohmann::json& attr);

    void ShowBadgeExamples();
}