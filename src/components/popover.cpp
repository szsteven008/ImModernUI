#include "popover.h"

#include "imgui.h"

namespace ImModernUI {
    void ShowPopoverExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Popover Examples", 
            ImVec2(0, 0), flags);
        ImGui::EndChild();
    }
}