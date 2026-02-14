#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>
namespace ImModernUI {
    /*
    {
        "label": "##Menubar", 
        "menus": [
            {
                "trigger": "", 
                "content": [
                    {
                        "type": "item", 
                        "text": "", 
                        "shortcut": "", 
                        "disabled": true|false
                    }, 
                    {
                        "type": "separator"
                    }, 
                    {
                        "type": "submenu", 
                        "submenu": {
                            "trigger": "", 
                            "subcontent": [
                                ...
                            ]
                        }
                    },
                    {
                        "type": "checkbox", 
                        "text": "", 
                        "checked": true|false
                    }, 
                    {
                        "type": "ratiogroup", 
                        "items": [
                            {
                                "label": "Andy", 
                                "value": "andy"
                            },
                            {
                                "label": "Benoit", 
                                "value": "benoit"
                            },
                            {
                                "label": "Luis", 
                                "value": "luis"
                            }
                        ],
                        "value": "benoit"
                    }
                ]
            }
        ]
    }
    */
    bool Menubar(
        nlohmann::json& attr, 
        std::function<void(const std::string& label)> handler
    );

    void ShowMenubarExamples();
}