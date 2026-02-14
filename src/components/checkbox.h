#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "##checkbox-{id}", 
        "description": "{description}"
        "disabled": true|false
    }
    */
    bool Checkbox(const nlohmann::json& attr, bool *v);

    void ShowCheckboxExamples();
}