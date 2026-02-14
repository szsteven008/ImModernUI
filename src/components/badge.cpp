#include "badge.h"

#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "themes.h"
#include <string>

namespace ImModernUI {
    struct BadgeStyle {
        static ImVec4 background(const std::string& variant) {
            if (variant == "primary") return UIThemes::primary();
            if (variant == "secondary") return UIThemes::secondary();
            if (variant == "destructive") return UIThemes::destructive();
            if (variant == "outline") return UIColors::color_transparent;
            return UIThemes::primary();
        }
        static ImVec4 foreground(const std::string& variant) {
            if (variant == "primary") return UIThemes::primary_foreground();
            if (variant == "secondary") return UIThemes::secondary_foreground();
            if (variant == "destructive") return UIColors::color_white;
            if (variant == "outline") return UIThemes::foreground();
            return UIThemes::primary_foreground();
        }
        static ImVec4 hover(const std::string& variant) {
            if (variant == "primary") {
                return ImVec4(
                    UIThemes::primary().x, 
                    UIThemes::primary().y, 
                    UIThemes::primary().z, 
                    0.9
                );
            }
            if (variant == "secondary") {
                return ImVec4(
                    UIThemes::secondary().x, 
                    UIThemes::secondary().y, 
                    UIThemes::secondary().z, 
                    0.9
                );
            }
            if (variant == "destructive") {
                return ImVec4(
                    UIThemes::destructive().x, 
                    UIThemes::destructive().y, 
                    UIThemes::destructive().z, 
                    0.9
                );                
            }
            if (variant == "outline") return UIThemes::accent();
            return ImVec4(
                    UIThemes::primary().x, 
                    UIThemes::primary().y, 
                    UIThemes::primary().z, 
                    0.9
                );
        }
        static ImVec4 hover_foreground(const std::string& variant) {
            if (variant == "outline") return UIThemes::accent_foreground();
            return foreground(variant);
        }
        static ImVec4 border(const std::string& variant) {
            if (variant == "outline") return UIThemes::border();
            return UIColors::color_transparent;
        }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_2(), UISizes::p_1());
        }
        static ImVec2 gap() { return ImVec2(UISizes::m_1(), UISizes::m_1()); }

        static float rounding() { return UISizes::rounded_full(); }
    };

    static bool rectangle_badge(
        const std::string& label, 
        const std::string& variant, 
        const std::string& icon
    ) {
        float height = BadgeStyle::padding().y * 2 + UISizes::size_3();
        float width = BadgeStyle::padding().x * 2;
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        width += label_size.x;
        if (!icon.empty()) {
            width += UISizes::size_3();
            width += BadgeStyle::gap().x;
        }

        auto id = ImGui::GetID(label.c_str());
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered = false;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto col = hovered ? 
            ImGui::GetColorU32(BadgeStyle::hover(variant)) : 
            ImGui::GetColorU32(BadgeStyle::background(variant));
        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            col, 
            BadgeStyle::rounding()
        );
        draw->AddRect(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(BadgeStyle::border(variant)), 
            BadgeStyle::rounding()
        );

        col = hovered ? 
            ImGui::GetColorU32(BadgeStyle::hover_foreground(variant)) : 
            ImGui::GetColorU32(BadgeStyle::foreground(variant));
        float x = bb.Min.x + BadgeStyle::padding().x;
        if (!icon.empty()) {
            ImGui::PushFont(UIFont::font_icon_sm());
            float y = bb.Min.y + (bb.Max.y - bb.Min.y - UISizes::size_3()) * 0.5;
            draw->AddText(
                ImVec2(x, y), 
                col, 
                icon.c_str()
            );
            ImGui::PopFont();
            x += UISizes::size_3() + BadgeStyle::gap().x;
        }

        float y = bb.Min.y + (bb.Max.y - bb.Min.y - label_size.y) * 0.5;
        draw->AddText(
            ImVec2(x, y), 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );

        return pressed;
    }

    bool circle_badge(
        const std::string& label, 
        const std::string& variant
    ) {
        float height = BadgeStyle::padding().y * 2 + UISizes::size_3();
        float width = height;
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );

        auto id = ImGui::GetID(label.c_str());
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered = false;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto col = hovered ? 
            ImGui::GetColorU32(BadgeStyle::hover(variant)) : 
            ImGui::GetColorU32(BadgeStyle::background(variant));
        auto draw = ImGui::GetWindowDrawList();
        auto center = ImVec2(
            (bb.Min.x + bb.Max.x) * 0.5, 
            (bb.Min.y + bb.Max.y) * 0.5
        );
        float radius = (bb.Max.x - bb.Min.x) * 0.5;
        draw->AddCircleFilled(
            center, 
            radius, 
            col, 
            64
        );
        draw->AddCircle(
            center, 
            radius, 
            col, 
            64
        );

        col = hovered ? 
            ImGui::GetColorU32(BadgeStyle::hover_foreground(variant)) : 
            ImGui::GetColorU32(BadgeStyle::foreground(variant));
        draw->AddText(
            ImVec2(
                center.x - label_size.x * 0.5 + UISizes::text_xs() * 0.08, 
                center.y - label_size.y * 0.5
            ), 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );

        return pressed;
    }

    bool Badge(const nlohmann::json& attr) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string variant = "primary";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string icon = "";
        if (attr.contains("icon")) 
            icon = attr["icon"].get<std::string>();
        std::string shape = "rectangle";
        if (attr.contains("shape"))
            shape = attr["shape"].get<std::string>();

        ImGui::PushFont(UIFont::font_medium_xs());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_Button, BadgeStyle::background(variant)}, 
            {ImGuiCol_Text, BadgeStyle::foreground(variant)}, 
            {ImGuiCol_Border, BadgeStyle::border(variant)}
        };
        for (const auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, ImGui::GetColorU32(col));
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_FramePadding, BadgeStyle::padding()}, 
            {ImGuiStyleVar_ItemSpacing, BadgeStyle::gap()}, 
        };
        for (const auto& [idx, val]: style_vars_1) {
            ImGui::PushStyleVar(idx, val);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_FrameRounding, BadgeStyle::rounding()}, 
            {ImGuiStyleVar_FrameBorderSize, 1.0}
        };
        for (const auto& [idx, val]: style_vars_2) {
            ImGui::PushStyleVar(idx, val);
        }

        bool pressed = false;
        if (shape == "circle") {
            pressed = circle_badge(
                label, 
                variant
            );
        } else {
            pressed = rectangle_badge(
                label, 
                variant, 
                icon
            );
        }
        
        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();

        return pressed;
    }

    void ShowBadgeExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Show Badge Examples", 
            ImVec2(0, 0), flags);
        {
            nlohmann::json attr;
            attr["label"] = "Badge";
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "Secondary";
            attr["variant"] = "secondary";
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "Destructive";
            attr["variant"] = "destructive";
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "Outline";
            attr["variant"] = "outline";
            Badge(attr);
        }

        {
            nlohmann::json attr;
            attr["label"] = "Verified##With Icon";
            attr["icon"] = ICON_BADGE_CHECK;
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "8##Primary";
            attr["shape"] = "circle";
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "99##Destructive";
            attr["variant"] = "destructive";
            Badge(attr);
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "20+##Outline";
            attr["variant"] = "outline";
            Badge(attr);
        }

        ImGui::EndChild();
    }
}