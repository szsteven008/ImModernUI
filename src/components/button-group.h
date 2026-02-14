#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>
#include <string>

namespace ImModernUI {
    /*
    {
        "label": "Button Group", 
        "size": "sm|md|lg", 
        "orientation": "horizontal|vertical"
        "buttons": [
            {
                "label": "button 1", 
                "type": "text|icon", 
                "value": ""
            }
        ]
    }
    */
    bool ButtonGroup(
        const nlohmann::json& attr, 
        std::function<void(const std::string&)> action
    );

    void ShowButtonGroupExamples();
}