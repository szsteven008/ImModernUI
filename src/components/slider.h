#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    /*
    {
        "label": "Slider Example", 
        "orientation": "horizontal|vertical"
        "min": 0,
        "max": 100,
        "step": 1
    }
    */
    bool Slider(const nlohmann::json& attr, int * v);

    void ShowSliderExamples();
}