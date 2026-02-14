#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "icon": "{icon}", 
        "text": {text}, 
        "promise": true|false
    }
    */
    bool Sonner(const nlohmann::json& attr);
    void UpdateSonner();

    void ShowSonnerExamples();
}