#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>
#include <string>
namespace ImModernUI {
    /*
    {
        "label": "{label}", 
        "placeholder": "", 
        "size": "sm|default", 
        "selected-icon-align": "left|right"
        "width": {width}
        "groups": [
            {
                "label": "{group label}", 
                "items": [
                    {
                        "label": "item 1", 
                        "value": ""
                    },
                    ...
                ]
            }
            ...
        ]
    }
    */
    bool select(
        const nlohmann::json& attr, 
        std::string& value, 
        std::function<bool(
            const nlohmann::json&, 
            const std::string& 
        )> trigger = nullptr
    );

    void ShowSelectExamples();
}