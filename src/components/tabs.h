#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "label": "Tabs", 
        "variant": "default|line", 
        "orientation": "horizontal|vertical", 
        "align": "default|center", 
        "items": [
            {
                "name": "", 
                "icon": "", 
                "disabled": true|false
            }
        ]
    }
    */
    bool Tabs(
        const nlohmann::json& attr, 
        int * v, 
        std::function<void(int)> action = [](int) {}, 
        float max_width = 0
    );

    void ShowTabsExamples();
}