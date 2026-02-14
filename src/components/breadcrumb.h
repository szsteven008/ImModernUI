#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "label": "##Breadcrumb", 
        "separator": "{separator}", 
        "items": [
            {
                "label": "{label}", 
                "type": "link|ellipsis|dropdown"
            }
        ]
    }
    */
    bool Breadcrumb(
        const nlohmann::json& attr, 
        std::function<void(const std::string&)> action
    );

    void ShowBreadcrumbExamples();
}