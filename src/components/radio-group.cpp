#include "radio-group.h"

#include "imgui_internal.h"
#include "label.h"
#include "lucide.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <string>
#include <vector>

namespace ImModernUI {
    struct RadioGroupStyle {
        static ImVec4 background() { return UIThemes::background(); }
        static ImVec4 foreground() { return UIThemes::primary(); }
        static ImVec4 border() { return UIThemes::input(); }

        static ImVec2 gap() { return ImVec2(UISizes::m_3(), UISizes::m_3()); }
        static ImVec2 inner_gap() { return ImVec2(UISizes::m_2(), UISizes::m_2()); }
    };

    static bool RadioButton(const std::string& label, bool on) {  
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
            RadioGroupStyle::inner_gap());

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + UISizes::size_4(), 
            pos.y + UISizes::size_4()
        };

        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);
        
        if (ImGui::ButtonBehavior(
                bb, 
                id, 
                nullptr, 
                nullptr
            )) on = !on;

        auto draw = ImGui::GetWindowDrawList();
        ImGui::PushFont(UIFont::font_icon());
        draw->AddText(
            pos, 
            ImGui::GetColorU32(RadioGroupStyle::border()), 
            ICON_CIRCLE
        );
        ImGui::PopFont();
        if (on) {
            draw->AddCircleFilled(
                ImVec2(
                    pos.x + UISizes::size_4() * 0.5, 
                    pos.y + UISizes::size_4() * 0.5
                ), 
                UISizes::size_4() * 0.25, 
                ImGui::GetColorU32(UIThemes::primary()), 
                128
            );
        }

        ImGui::SameLine();
        ImModernUI::Label(
            label, 
            true, 
            ImGui::GetColorU32(RadioGroupStyle::foreground())
        );
        
        ImGui::PopID();
        ImGui::PopStyleVar();

        return on;
    }

    bool RadioGroup(const nlohmann::json& attr, int* v) {
        if (!attr.contains("label") || 
            !attr.contains("data")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string direction = "horizon";
        if (attr.contains("direction")) 
            direction = attr["direction"].get<std::string>();
        auto data = attr["data"];

        ImGui::PushFont(UIFont::font_medium_sm());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_FrameBg, RadioGroupStyle::background()}, 
            {ImGuiCol_Text, RadioGroupStyle::foreground()}, 
            {ImGuiCol_Border, RadioGroupStyle::border()},
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_ItemSpacing, RadioGroupStyle::gap()}, 
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        ImGui::BeginGroup();

        auto items = data.get<std::vector<nlohmann::json>>();
        for (const auto& item: items) {
            std::string item_label = item["label"].get<std::string>();
            int item_v = item["value"].get<int>();

            if (RadioButton(item_label, (item_v == *v))) {
                *v = item_v;
            }

            if (direction == "horizon" && item != items.back()) ImGui::SameLine();
        }

        ImGui::EndGroup();
        ImGui::PopID();

        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();

        return true;
    }

    void ShowRadioGroupExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        ImGui::BeginChild("##Radio Group Examples", 
            ImVec2(0, 0), flags);

        ImGui::SeparatorText("Horizon");
        {
            static int v = 0;
            ImModernUI::RadioGroup(
                R"(
                    {
                        "label": "##Radio Group horizon", 
                        "direction": "horizon", 
                        "data": [
                            {
                                "label": "Default", 
                                "value": 0
                            },
                            {
                                "label": "Comfortable", 
                                "value": 1
                            },
                            {
                                "label": "Compact", 
                                "value": 2
                            }
                        ]
                    }
                )"_json, 
                &v
            );
        }

        ImGui::SeparatorText("Vertical");
        {
            static int v = 0;
            ImModernUI::RadioGroup(
                R"(
                    {
                        "label": "##Radio Group horizon", 
                        "direction": "vertical", 
                        "data": [
                            {
                                "label": "Option-One", 
                                "value": 0
                            },
                            {
                                "label": "Option-Two", 
                                "value": 1
                            }
                        ]
                    }
                )"_json, 
                &v
            );
        }

        ImGui::EndChild();
    }
}