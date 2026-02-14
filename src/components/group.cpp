#include "group.h"
#include "imgui.h"

namespace ImModernUI {
    void BeginGroup(
        const ImVec2 spacing /* = ImVec2(
            UISizes::m_2(), 
            UISizes::m_2()
        ) */
    ) {
        ImGui::BeginGroup();
        ImGui::PushStyleVar(
            ImGuiStyleVar_ItemSpacing, spacing
        );
    }

    void EndGroup() {
        ImGui::PopStyleVar();
        ImGui::EndGroup();
    }
}