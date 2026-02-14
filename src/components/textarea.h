#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "Input Area", 
        "placeholder": "{placeholder}", 
        "description": "{discription}", 
        "action": "{action}"
        "disabled": true|false
    }
    */
    bool Textarea(
        const nlohmann::json& attr, 
        char * buf, 
        int buf_size, 
        std::function<void(char * buf, int buf_size)> action = nullptr, 
        const ImVec2& size = ImVec2(0, 0)
    );

    void ShowTextareaExamples();
}