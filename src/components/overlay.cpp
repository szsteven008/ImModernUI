#include "overlay.h"

#include "imgui.h"

namespace ImModernUI {
    bool Overlay(
        const ImVec4 bg /* = UIColors::color_transparent */
    ) {
        bool open = true;

        auto& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 
            ImGui::GetColorU32(bg));
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
        if (ImGui::Begin(
            "##overlay", 
            nullptr, 
            flags
        )) {
            if (ImGui::InvisibleButton(
                "##overlay button", 
                io.DisplaySize)
            ) open = false;
        }
        ImGui::End();
        ImGui::PopStyleColor();

        return open;
    }
}