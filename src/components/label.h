#pragma once

#include "imgui.h"
#include "themes.h"
#include <string>

namespace ImModernUI {
    bool Label(
        const std::string& label, 
        bool target = true, 
        const int col = ImGui::GetColorU32(UIThemes::foreground())
    );

    void ShowLabelExamples();
}