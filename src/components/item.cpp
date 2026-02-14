#include "item.h"

#include "imgui.h"
#include "nlohmann/json.hpp"

namespace ImModernUI {
    bool Item(const nlohmann::json& attr) {
        return true;
    }

    void ShowItemExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Item Examples", 
            ImVec2(0, 0), flags);

        ImGui::EndChild();
    }
}