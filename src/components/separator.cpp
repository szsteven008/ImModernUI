#include "separator.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "label.h"
#include "themes.h"

namespace ImModernUI {
    bool Separator(
        const std::string& orientation /* = "horizontal" */, 
        float size /* = .0f */
    ) {
        auto pos = ImGui::GetCursorScreenPos();
        auto avail_size = ImGui::GetContentRegionAvail();
        if (size == 0.0f) {
            size = (orientation == "horizontal") ? 
                ImGui::GetContentRegionAvail().x : 
                ImGui::GetContentRegionAvail().y;
        }

        float x = (orientation == "horizontal") ? 
            (pos.x + size) : (pos.x + 1.0);
        float y = (orientation == "horizontal") ? 
            (pos.y + 1.0) : (pos.y + size);
        ImRect bb {
            pos.x, pos.y, 
            x, y
        };
        ImGui::ItemSize(bb.GetSize());

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            pos, 
            ImVec2(x, y), 
            ImGui::GetColorU32(UIThemes::border())
        );

        return true;
    }

    void ShowSeparatorExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;

        ImGui::BeginChild("##Separator Examples", 
            ImVec2(0, 0), flags);
        ImModernUI::Label("Radix Primitives", false);
        ImGui::PushStyleColor(ImGuiCol_Text, 
            UIThemes::muted_foreground());
        ImGui::TextUnformatted("An open-source UI component library.");
        ImGui::PopStyleColor();
        float width = 
            ImGui::CalcTextSize("An open-source UI component library.").x;
        ImModernUI::Separator("horizontal", width);

        float height = ImGui::CalcTextSize("Blog").y + 
            ImGui::GetStyle().WindowPadding.y;
        ImGui::TextUnformatted("Blog");
        ImGui::SameLine();
        ImModernUI::Separator("vertical", height);
        ImGui::SameLine();
        ImGui::TextUnformatted("Docs");
        ImGui::SameLine();
        ImModernUI::Separator("vertical", height);
        ImGui::SameLine();
        ImGui::TextUnformatted("Source");

        ImGui::EndChild();
    }
}