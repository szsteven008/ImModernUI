#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "Button",
        "variant": "primary|outline|secondary|ghost|destructive|link",
        "size": "xs|sm|md|lg|icon-sm|icon|icon-lg|full-sm|full|full-lg",
        "shape": "rectangle|circle"
        "icon": ICON_GIT_BRANCH, 
        "icon-align": "left|right", 
        "corner": top|bottom|left|right|all|none, 
        "disabled": true|false
    }
    */
    bool Button(const nlohmann::json& attr);
    ImVec2 CalcButtonSize(
        const nlohmann::json& attr
    );

    void ShowButtonExamples();
}