#pragma once

#include "imgui.h"
#include <string>

namespace ImModernUI {
    bool Spinner(
        const std::string& label, 
        ImDrawList * draw = nullptr
    );

    void ShowSpinnerExamples();
}