#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "lable": "Toggle Group", 
        "type": "multiple|single", 
        "variant": "default|outline", 
        "size": "default|sm|lg",
        "spacing": true|false,  
        "disabled": true|false, 
        "items": [
            {
                "label": "item 1", 
                "icon": "icon 1", 
                "on": "yellow_500", 
                "corner": top|bottom|left|right|all|none
            },
            ...
        ]
    }
    */
    bool ToggleGroup(const nlohmann::json& attr, bool * on);

    void ShowToggleGroupExamples();
}