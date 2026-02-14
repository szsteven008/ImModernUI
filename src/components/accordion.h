#pragma once

#include "imgui.h"
#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "##Accordion-{id}",
        "data": [
            {
                "trigger": "{trigger}",
                "content": "{content}"
            },
            {
                ...
            }
        ]
    }
    */
    bool Accordion(
        const nlohmann::json& attr, 
        const ImVec2 size_arg = ImVec2(0, 0)
    );

    void ShowAccordionExamples();
}