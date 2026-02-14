#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "Input Text", 
        "type": "file|text|password|invalid", 
        "placeholder": "{placeholder}", 
        "disabled": true|false, 
        "border": true|false
    }
    */
    bool Input(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size
    );

    void ShowInputExamples();
}