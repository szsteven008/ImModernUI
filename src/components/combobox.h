#pragma once

#include "nlohmann/json_fwd.hpp"
#include <vector>

namespace ImModernUI {
    /*
    {
        "label": "", 
        "placeholder": "", 
        "multiple": false|true, 
        "groups": [
            {
                "value": "", 
                "items":[
                    "", ...
                ]
            },
            ...
        ]
    }
    */
    bool Combobox(
        const nlohmann::json& attr, 
        std::vector<std::string>& value
    );

    void ShowComboboxExamples();
}