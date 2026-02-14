#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "##Alert-{id}", 
        "variant": "default|destructive"
        "icon": {icon}, 
        "title": "{title}", 
        "description": [{
            "text": {text},
            "items": [{items}]
        }]
    }
    */
    bool Alert(
        const nlohmann::json& attr, 
        const ImVec2& size_arg = ImVec2(0, 0)
    );

    void ShowAlertExamples();
}