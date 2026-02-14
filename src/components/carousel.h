#pragma once

#include "nlohmann/json_fwd.hpp"
#include <functional>

namespace ImModernUI {
    /*
    {
        "label": "{label}", 
        "orientation": "horizontal|vertical", 
        "total": {total}
        "visible": {visible}
    }
    */
    bool Carousel(
        const nlohmann::json& attr, 
        std::function<void(int)> item, 
        int * v
    );

    void ShowCarouselExamples();
}