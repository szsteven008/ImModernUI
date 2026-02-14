#include "switch.h"

#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "label.h"
#include "themes.h"

namespace ImModernUI {
    struct SwitchStyle {
        static ImVec4 background(bool checked) {
            if (checked) return UIThemes::primary();
            return (UIThemes::current_scheme == UIThemeScheme::Dark) ? 
                ImVec4(
                    UIThemes::input().x, 
                    UIThemes::input().y, 
                    UIThemes::input().z, 
                    0.80
                ) : UIThemes::input();
        }

        static ImVec4 foreground(bool checked) {
            if (UIThemes::current_scheme == UIThemeScheme::Dark) {
                return (checked ? UIThemes::primary_foreground() : 
                    UIThemes::foreground());
            }
            return UIThemes::background();
        }

        static float rounding() { return UISizes::rounded_full(); }
        static ImVec2 gap() { return ImVec2(UISizes::m_2(), UISizes::m_2()); }
    };

    bool Switch(const std::string& label, bool checked) {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
            SwitchStyle::gap());

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        auto pos = ImGui::GetCursorScreenPos();
        float w = UISizes::w_8(), h = 1.15f * UISizes::base_font_size;
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + w, 
            pos.y + h
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        if (ImGui::ButtonBehavior(
            bb, 
            id, 
            nullptr, 
            nullptr
        )) checked = !checked;

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(SwitchStyle::background(checked)), 
            SwitchStyle::rounding()
        );

        float radius = UISizes::size_4() * 0.5;
        float x = bb.Min.x + radius + 1.0;
        if (checked) x = bb.Max.x - radius - 1.0;
        float y = (bb.Min.y + bb.Max.y) * 0.5;
        draw->AddCircleFilled(
            ImVec2(x, y), 
            radius, 
            ImGui::GetColorU32(SwitchStyle::foreground(checked)), 
            64
        );

        ImGui::SameLine();
        ImModernUI::Label(label);

        ImGui::PopID();
        ImGui::PopStyleVar();

        return checked;
    }

    void ShowSwitchExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Switch Examples", 
            ImVec2(0, 0), flags);
        static bool checked = false;
        checked = Switch("Airplane Mode", checked);
        ImGui::EndChild();
    }
}