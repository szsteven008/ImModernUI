#pragma once

#include "nlohmann/json_fwd.hpp"
namespace ImModernUI {
    /*
    {
        "label": "", 
        "groups": [
            {
                "label": "", 
                "type": "default|checkboxes|ratiogroup"
                "items": [
                    {
                        "type": "text"
                        "label": "", 
                        "shortcut": ""
                    },
                    {
                        "type": "submenu"
                        "label": "", 
                        "groups": [
                            ...
                        ]
                    }
                    ...
                ]
            }, 
            ...
        ]
    }
    */
    bool DropdownMenu(
        const nlohmann::json& attr
    );

    void ShowDropdownMenuExamples();
}