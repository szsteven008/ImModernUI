#include "link.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "themes.h"

namespace ImModernUI {
    bool link(const std::string label) {
        auto id = ImGui::GetID(label.c_str());

        ImGui::TextUnformatted(label.c_str());

        ImRect bb {
            ImGui::GetItemRectMin(), 
            ImGui::GetItemRectMax()
        };
        ImGui::ItemAdd(bb, id);

        bool hovered;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        if (hovered) {
            draw->AddLine(
                ImVec2(
                    bb.Min.x, 
                    bb.Max.y
                ), 
                ImVec2(
                    bb.Max.x, 
                    bb.Max.y
                ), 
                ImGui::GetColorU32(UIThemes::foreground())
            );

            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        }

        return pressed;
    }
}