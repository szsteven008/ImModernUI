#include "dropdownmenu.h"

#include "imgui.h"

namespace ImModernUI {
    bool DropdownMenu(
        const nlohmann::json& attr
    ) {
        return true;
    }

    void ShowDropdownMenuExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild(
            "##Dropdown menu examples", 
            ImVec2(0, 0), 
            flags
        );

        ImGui::SeparatorText("Dropdown Menu");
        ImGui::SeparatorText("Checkboxes");
        ImGui::SeparatorText("Radio Group");
        ImGui::SeparatorText("Dialog");

        ImGui::EndChild();
    }
}