#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "{label}", 
        "icon": "{icon}", 
        "variant": "default|outline"
        "size": "default|xs|sm|lg",
        "disabled": true|false, 
        "on": "blue_500", 
        "corner": top|bottom|left|right|all|none
    }
    */
    bool Toggle(const nlohmann::json& attr, bool * on);

    void ShowToggleExamples();
}