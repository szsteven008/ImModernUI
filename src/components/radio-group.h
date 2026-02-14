#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": {ratio-group-id},
        "direction": "horizon|vertical",
        "data": [
            {
                "label": "{label}", 
                "value": {value}
            }
        ]
    }
    */
    bool RadioGroup(const nlohmann::json& attr, int* v);

    void ShowRadioGroupExamples();
}