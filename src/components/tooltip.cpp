#include "tooltip.h"

#include "button.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <string>

namespace ImModernUI {
    struct TooltipStyle {
        static ImVec4 background() { return UIThemes::foreground(); }
        static ImVec4 foreground() { return UIThemes::background(); }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_3(), 1.5 * UISizes::spacing()); 
        }

        static float rounding() { return UISizes::rounded_md(); }
        static float side_offset() { return 1.0; }
        static float triangle_size() { return 2.5 * UISizes::spacing(); }
    };

    static void draw_triangle(float offset_x) {
        auto min = ImGui::GetItemRectMin();
        auto max = ImGui::GetItemRectMax();
        auto center = ImVec2(
            (min.x + max.x) * 0.5 + offset_x, 
            max.y - 2.0
        );
        ImRect bb {
            center.x - TooltipStyle::triangle_size(), 
            center.y, 
            center.x + TooltipStyle::triangle_size(), 
            center.y + TooltipStyle::triangle_size()
        };
                
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, ImGui::GetID("triangle"));
        ImGui::GetWindowDrawList()->AddTriangleFilled(
            bb.Min, 
            ImVec2(bb.Max.x, bb.Min.y), 
            ImVec2(center.x, bb.Max.y), 
            ImGui::GetColorU32(TooltipStyle::background())
        );
    }

    bool Tooltip(
        const nlohmann::json& attr, 
        std::function<bool(const nlohmann::json&)> trigger
    ) {
        if (!attr.contains("label") || 
            !attr.contains("content") || 
            !attr.contains("trigger")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string content = attr["content"].get<std::string>();
        auto trigger_attr = attr["trigger"];

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        trigger(trigger_attr);
        if (ImGui::IsItemHovered()) {
            ImGui::PushFont(UIFont::font_regular_xs());

            auto min = ImGui::GetItemRectMin();
            auto max = ImGui::GetItemRectMax();
            auto content_size = 
                ImGui::CalcTextSize(content.c_str());

            float width = TooltipStyle::padding().x * 2 + content_size.x;
            float height = TooltipStyle::padding().y * 2 + 
                content_size.y + TooltipStyle::triangle_size();

            auto pos = ImVec2(
                (min.x + max.x - width) * 0.5, 
                min.y - height - TooltipStyle::side_offset()
            );
            float offset_x = 0.0;
            if (pos.x < 0) {
                offset_x = pos.x;
                pos.x = 0;
            }
            ImGui::SetNextWindowPos(pos);

            std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
                {ImGuiCol_WindowBg, UIColors::color_transparent}, 
                {ImGuiCol_FrameBg, TooltipStyle::background()}, 
                {ImGuiCol_Text, TooltipStyle::foreground()}, 
                {ImGuiCol_Border, UIColors::color_transparent},
            };
            for (auto& [idx, col]: style_colors) {
                ImGui::PushStyleColor(idx, col);
            }

            std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
                {ImGuiStyleVar_WindowPadding, ImVec2(0, 0)},
                {ImGuiStyleVar_ItemSpacing, ImVec2(0, 0)}, 
                {ImGuiStyleVar_FramePadding, TooltipStyle::padding()},                
            };
            for (const auto& [idx, var]: style_vars_1) {
                ImGui::PushStyleVar(idx, var);
            }

            std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
                {ImGuiStyleVar_WindowRounding, TooltipStyle::rounding()}, 
                {ImGuiStyleVar_FrameRounding, TooltipStyle::rounding()}, 
            };
            for (const auto& [idx, var]: style_vars_2) {
                ImGui::PushStyleVar(idx, var);
            }

            ImGui::SetNextWindowFocus();
            ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
            flags |= ImGuiWindowFlags_AlwaysAutoResize;
            ImGui::Begin(label.c_str(), nullptr, flags);
            ImGuiChildFlags child_flags = ImGuiChildFlags_AutoResizeX;
            child_flags |= ImGuiChildFlags_AutoResizeY;
            child_flags |= ImGuiChildFlags_FrameStyle;
            ImGui::BeginChild(id, ImVec2(0, 0), child_flags);
            ImGui::TextUnformatted(content.c_str());
            ImGui::EndChild();

            draw_triangle(offset_x);

            ImGui::End();
            ImGui::PopStyleVar(style_vars_2.size());
            ImGui::PopStyleVar(style_vars_1.size());
            ImGui::PopStyleColor(style_colors.size());
            ImGui::PopFont();
        }
        ImGui::PopID();

        return true;
    }

    void ShowTooltipExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("Tooltip Examples", 
            ImVec2(0, 0), flags);
        {
            nlohmann::json attr;
            attr["label"] = "Tooltip Examples";
            attr["content"] = "Add to library";
            attr["trigger"]["label"] = "Hover";
            attr["trigger"]["variant"] = "outline";
            attr["trigger"]["size"] = "md";
            Tooltip(attr, ImModernUI::Button);
        }
        ImGui::EndChild();
    }

}