#include "accordion.h"

#include "lucide.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "separator.h"
#include "themes.h"
#include <string>
#include <tuple>
#include <vector>

namespace ImModernUI {
    struct AccordionStyle {
        static ImVec4 background() { return UIThemes::background(); }
        static ImVec4 foreground() { return UIThemes::foreground(); }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_2(), UISizes::p_4()); 
        }
        static ImVec2 gap() { 
            return ImVec2(UISizes::m_4(), UISizes::m_2()); 
        }

    };

    static bool AccordionTrigger(const std::string& label, bool open) {
        auto pos = ImGui::GetCursorScreenPos();        
        float width = ImGui::GetContentRegionAvail().x;
        float height = UISizes::size_4() + AccordionStyle::padding().y * 2;

        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };

        auto id = ImGui::GetID(label.c_str());
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered;
        if (ImGui::ButtonBehavior(
                bb, 
                id, 
                &hovered, 
                nullptr
            )) open = !open;


        auto draw = ImGui::GetWindowDrawList();

        ImGui::PushFont(UIFont::font_medium_sm());
        auto label_size = ImGui::CalcTextSize(label.c_str());
        float x = bb.Min.x;
        float y = bb.Min.y + (height - label_size.y) * 0.5;
        draw->AddText(
            ImVec2(x, y), 
            ImGui::GetColorU32(AccordionStyle::foreground()),
            label.c_str()
        );

        if (hovered) {
            draw->AddLine(
                ImVec2(
                    x, 
                    y + label_size.y + UISizes::underline_offset_1()
                ), 
                ImVec2(
                    x + label_size.x,  
                    y + label_size.y + UISizes::underline_offset_1()
                ), 
                ImGui::GetColorU32(AccordionStyle::foreground())
            );
        }
        ImGui::PopFont();

        ImGui::PushFont(UIFont::font_icon());
        x = bb.Max.x - UISizes::size_4();
        y = bb.Min.y + (height - UISizes::size_4()) * 0.5;

        draw->AddText(
            ImVec2(x, y), 
            ImGui::GetColorU32(UIThemes::muted_foreground()), 
            open ? ICON_CHEVRON_UP : ICON_CHEVRON_DOWN
        );
        ImGui::PopFont();

        return open;
    }

    static bool AccordionItem(const nlohmann::json& item, bool is_open) {
        std::string trigger = item["trigger"].get<std::string>();
        std::string content = item["content"].get<std::string>();

        is_open = AccordionTrigger(trigger.c_str(), is_open);        
        if (is_open) {
            float width = ImGui::GetContentRegionAvail().x;
            ImGui::PushTextWrapPos(
                ImGui::GetCursorPosX() + width
            );
            ImGui::TextUnformatted(content.c_str());
            ImGui::PopTextWrapPos();
        }

        return is_open;
    }

    bool Accordion(
        const nlohmann::json& attr, 
        const ImVec2 size_arg /* = ImVec2(0, 0) */
    ) {
        if (!attr.contains("label") || !attr.contains("data"))
            return false;

        std::string label = attr["label"].get<std::string>();
        auto data = attr["data"];
        if (!data.is_array()) return false;

        auto accordion_id = ImGui::GetID(label.c_str());
        ImGui::PushID(accordion_id);
        ImGui::PushFont(UIFont::font_regular_sm());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_ChildBg, AccordionStyle::background()}, 
            {ImGuiCol_Text, AccordionStyle::foreground()}, 
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars {
            {ImGuiStyleVar_WindowPadding, AccordionStyle::padding()},
            {ImGuiStyleVar_ItemSpacing, AccordionStyle::gap()},
        };
        for (auto& [idx, var]: style_vars) {
            ImGui::PushStyleVar(idx, var);
        }

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        if (ImGui::BeginChild(accordion_id, 
            size_arg, flags)) {
            auto items = data.get<std::vector<nlohmann::json>>();
            for (int i=0; i<items.size(); ++i) {
                auto activate_item = ImGui::GetStateStorage()->GetInt(accordion_id, 
                    -1);
                if (AccordionItem(items[i], (activate_item == i))) {
                    ImGui::GetStateStorage()->SetInt(accordion_id, i);
                } else if (activate_item == i) {
                    ImGui::GetStateStorage()->SetInt(accordion_id, -1);
                }
                if (i < (items.size() - 1)) ImModernUI::Separator();
            }
        }
        ImGui::EndChild();

        ImGui::PopStyleVar(style_vars.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();
        ImGui::PopID();

        return true;
    }

    void ShowAccordionExamples() {
        nlohmann::json attr = R"(
            {
                "label": "Accordion",
                "data": [
                    {
                        "trigger": "Product Information",
                        "content": "Our flagship product combines cutting-edge technology with sleek design. Built with premium materials, it offers unparalleled performance and reliability.\nKey features include advanced processing capabilities, and an intuitive user interface designed for both beginners and experts."
                    },
                    {
                        "trigger": "Shipping Details",
                        "content": "We offer worldwide shipping through trusted courier partners. Standard delivery takes 3-5 business days, while express shipping ensures delivery within 1-2 business days.\nAll orders are carefully packaged and fully insured. Track your shipment in real-time through our dedicated tracking portal."
                    },
                    {
                        "trigger": "Return Policy",
                        "content": "We stand behind our products with a comprehensive 30-day return policy. If you&apos;re not completely satisfied, simply return the item in its original condition.\nOur hassle-free return process includes free return shipping and full refunds processed within 48 hours of receiving the returned item."
                    }
                ]
            }
        )"_json;

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild(
            "##Accordion Examples", 
            ImVec2(0, 0), 
            flags
        );
        Accordion(attr, ImVec2(UISizes::w_96(), 0));
        ImGui::EndChild();
    }
}