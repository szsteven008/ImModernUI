#include "checkbox.h"

#include "group.h"
#include "imgui_internal.h"
#include "label.h"
#include "lucide.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "themes.h"
#include "nlohmann/json.hpp"
#include <format>
#include <string>

namespace ImModernUI {
    struct CheckboxStyle {
        static ImVec4 background() { return UIThemes::background(); }
        static ImVec4 foreground() { return UIThemes::foreground(); }
        static ImVec4 description() { return UIThemes::muted_foreground(); }
        static ImVec4 border() { return UIThemes::input(); }

        static ImVec2 padding() { return ImVec2(0, 0); }
        static ImVec2 gap() { return ImVec2(UISizes::m_2(), UISizes::m_2()); }
        static float rounding() { return UISizes::rounded_xs(); }
        static float border_size() { return UISizes::border_0(); }
        static float checkbox_size() { return UISizes::size_4(); }
    };

    static bool add_checkbox(const char * label, bool checked, bool disabled) {
        auto id = ImGui::GetID(label);
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + CheckboxStyle::checkbox_size(), 
            pos.y + CheckboxStyle::checkbox_size()
        };

        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRect(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(CheckboxStyle::border()), 
            CheckboxStyle::rounding()
        );

        if (!disabled) {
            bool hover, held;
            bool pressed = ImGui::ButtonBehavior(bb, id, 
                &hover, &held);
            if (pressed) checked = !checked;
        }

        if (checked) {
            draw->AddRectFilled(
                ImVec2(bb.Min.x + 1.0, bb.Min.y + 1.0), 
                ImVec2(bb.Max.x - 1.0, bb.Max.y - 1.0), 
                ImGui::GetColorU32(UIThemes::primary()), 
                CheckboxStyle::rounding()
            );

            ImGui::PushFont(UIFont::font_icon_sm());
            float padding = UISizes::size_4() - UISizes::size_3();
            auto checked_flag_pos = ImVec2(
                bb.Min.x + padding * 0.5, 
                bb.Min.y + padding * 0.5
            );
            draw->AddText(
                checked_flag_pos, 
                ImGui::GetColorU32(UIThemes::primary_foreground()), 
                ICON_CHECK
            );
            ImGui::PopFont();
        }

        return checked;
    }

    bool Checkbox(const nlohmann::json& attr, bool *v) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();

        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();
        bool has_description = attr.contains("description");
        std::string description;
        if (has_description) description = 
            attr["description"].get<std::string>();

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);
        ImGui::PushFont(UIFont::font_regular_sm());

        ImModernUI::BeginGroup();
        std::string label_checkbox = std::format("##{}", id);
        *v = add_checkbox(label_checkbox.c_str(), *v, disabled);
        ImGui::SameLine();
        ImModernUI::BeginGroup();
        ImModernUI::Label(
            label, 
            true, 
            disabled ? ImGui::GetColorU32(CheckboxStyle::description()) : 
                ImGui::GetColorU32(CheckboxStyle::foreground())
        );
        if (has_description) {
            auto& style = ImGui::GetStyle();
            ImGui::PushStyleColor(ImGuiCol_Text, 
                UIThemes::muted_foreground());
            ImGui::TextWrapped("%s", description.c_str());
            ImGui::PopStyleColor();
        }
        ImModernUI::EndGroup();
        ImModernUI::EndGroup();

        if (ImGui::IsItemHovered() && disabled) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
        } else {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        }

        ImGui::PopFont();
        ImGui::PopID();

        return true;
    }

    void ShowCheckboxExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Checkbox Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Basic");
        {
            static bool v = false;
            nlohmann::json attr;
            attr["label"] = "Accept terms and conditions";
            ImModernUI::Checkbox(attr, &v);
        }
        
        ImGui::SeparatorText("Description");
        {
            ImGui::PushTextWrapPos(
                ImGui::GetCursorPosX() + UISizes::w_72()
            );
            static bool v = true;
            nlohmann::json attr;
            attr["label"] = "Accept terms and conditions##with description";
            attr["description"] = "By clicking this checkbox, you agree to the terms and conditions.";
            ImModernUI::Checkbox(attr, &v);
            ImGui::PopTextWrapPos();
        }
        
        ImGui::SeparatorText("Disabled");
        {
            static bool v = false;
            nlohmann::json attr;
            attr["label"] = "Enable notifications";
            attr["disabled"] = true;
            ImModernUI::Checkbox(attr, &v);
        }
        
        ImGui::EndChild();
    }
}