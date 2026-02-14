#pragma once

#include "imgui.h"
#include <string>

namespace ImModernUI {
    bool BeginScrollArea(
        const std::string& label,
        const ImVec2& size_arg, 
        const std::string orientation = "vertical"
    );
    void EndScrollArea();

    void ShowScrollAreaExamples();
}