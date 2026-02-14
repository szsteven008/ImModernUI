#include "label.h"

#include "fonts.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace ImModernUI {
    bool Label(
        const std::string& label, 
        bool target /* = true */, 
        const int col /* = ImGui::GetColorU32(UIThemes::foreground()) */
    ) {
        ImGui::PushFont(UIFont::font_medium_sm());
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );

        float height = (target ? ImGui::GetItemRectSize().y : label_size.y);
        auto pos = ImGui::GetCursorScreenPos();
        float x = pos.x;
        float y = pos.y + height * 0.5;
    
        ImRect bb {
            x, 
            y - label_size.y * 0.5f, 
            x + label_size.x, 
            y + label_size.y * 0.5f
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, ImGui::GetID(label.c_str()));

        auto draw = ImGui::GetWindowDrawList();
        draw->AddText(
            bb.Min, 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );

        ImGui::PopFont();

        return true;
    }

    void ShowLabelExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Label Examples", 
            ImVec2(0, 0), flags);
        auto pos = ImGui::GetCursorScreenPos();
        Label(
            "Accept terms and conditions", 
            false
        );
        ImGui::EndChild();
    }
}