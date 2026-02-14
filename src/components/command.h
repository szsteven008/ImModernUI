#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "label": "{label}", 
        "placeholder": "{placeholder}", 
        "dialog": true|false
        "groups": [
            {
                "label": "{label}", 
                "items": [
                    {
                        "icon": "", 
                        "label": "", 
                        "shortcut": "", 
                        "disabled": true|false
                    }
                ]
            }
        ]
    }
    */
    bool Command(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size, 
        std::function<void(const std::string&)> handler
    );

    void ShowCommandExamples();
}