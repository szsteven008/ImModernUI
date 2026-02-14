#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "label": "", 
        "image": ""
        "title": "{title}", 
        "description": "{description}"
    }
    */
    bool Card(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        nlohmann::json& data, 
        std::function<void(const nlohmann::json&)> action = nullptr, 
        std::function<void(nlohmann::json&)> content = nullptr, 
        std::function<void(const nlohmann::json&)> footer = nullptr
    );

    void ShowCardExamples();
}