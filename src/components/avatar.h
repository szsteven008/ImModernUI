#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "{label}",
        "avatar": "{avatar image}", 
        "rounding": "full|xs|sm|md|lg",
        "grayscale": false
    }
    */
    bool Avatar(const nlohmann::json& attr);

    void ShowAvatarExamples();
}