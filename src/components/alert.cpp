#include "alert.h"

#include "lucide.h"
#include "nlohmann/json.hpp"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <string>

namespace ImModernUI {
    struct AlertStyle {
        static ImVec4 background() { return UIThemes::card(); }
        static ImVec4 foreground(const std::string& variant) {
            if (variant == "destructive") return UIThemes::destructive();
            return UIThemes::card_foreground();
        }
        static ImVec4 border() { return UIThemes::border(); }
        static ImVec4 description(const std::string& variant) {
            if (variant == "destructive") 
                return ImVec4(
                    UIThemes::destructive().x, 
                    UIThemes::destructive().y, 
                    UIThemes::destructive().z, 
                    0.9
                );
            return UIThemes::muted_foreground();
        }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_4(), UISizes::p_3()); 
        }
        static ImVec2 gap() {
            return ImVec2(UISizes::m_3(), 0.5 * UISizes::spacing());
        }
        static ImVec2 gap_description() {
            return ImVec2(UISizes::m_1(), UISizes::m_1());
        }
        static float rounding() { return UISizes::rounded_lg(); }
        static float border_size() { return UISizes::border_1(); }
    };

    bool Alert(
        const nlohmann::json& attr, 
        const ImVec2& size_arg /* = ImVec2(0, 0) */
    ) {
        if (!attr.contains("label") || 
            !attr.contains("icon") || 
            !attr.contains("title")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string variant = "default";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string icon = attr["icon"].get<std::string>();
        std::string title = attr["title"].get<std::string>();
        bool has_description = false;
        nlohmann::json description;
        if (attr.contains("description")) {
            description = attr["description"];
            has_description = true;
        }

        ImGui::PushID(ImGui::GetID(label.c_str()));
        ImGui::PushFont(UIFont::font_regular_sm());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_ChildBg, AlertStyle::background()}, 
            {ImGuiCol_Text, AlertStyle::foreground(variant)}, 
            {ImGuiCol_Border, AlertStyle::border()},
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, AlertStyle::padding()},
            {ImGuiStyleVar_FramePadding, AlertStyle::padding()},
            {ImGuiStyleVar_ItemSpacing, AlertStyle::gap()}, 
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_ChildBorderSize, AlertStyle::border_size()}, 
            {ImGuiStyleVar_ChildRounding, AlertStyle::rounding()}, 
        };
        for (const auto& [idx, var]: style_vars_2) {
            ImGui::PushStyleVar(idx, var);
        }

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_Borders;
        if (ImGui::BeginChild(label.c_str(), 
            size_arg, flags)) {
            ImGui::PushFont(UIFont::font_icon());
            ImGui::TextUnformatted(icon.c_str());
            ImGui::PopFont();

            ImGui::SameLine();

            ImGui::BeginGroup();
            ImGui::PushFont(UIFont::font_medium_sm());
            ImGui::TextUnformatted(title.c_str());
            ImGui::PopFont();

            if (has_description) {
                ImGui::PushStyleColor(ImGuiCol_Text, 
                    AlertStyle::description(variant));
                for (const auto& desc: description) {
                    if (desc.contains("text")) {
                        std::string text = desc["text"].get<std::string>();
                        ImGui::TextUnformatted(text.c_str());
                    }
                    if (desc.contains("items")) {
                        for (const auto& item: desc["items"]) {
                            const char * bullet = "\u2022";
                            ImGui::TextUnformatted(bullet);
                            ImGui::SameLine();
                            auto val = item.get<std::string>();
                            ImGui::TextUnformatted(val.c_str());
                        }
                    }
                }
                ImGui::PopStyleColor();
            }
            ImGui::EndGroup();
        }
        ImGui::EndChild();

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());

        ImGui::PopFont();
        ImGui::PopID();

        return true;
    }

    void ShowAlertExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Alert Examples", 
            ImVec2(0, 0), flags);

        ImVec2 size(UISizes::w_96(), 0);
        {
            nlohmann::json attr;
            attr["label"] = "##Alert default";
            attr["variant"] = "default";
            attr["icon"] = ICON_CIRCLE_CHECK;
            attr["title"] = "Success! Your changes have been saved";
            attr["description"] = R"(
                [
                    {
                        "text": "This is an alert with icon, title and description."
                    }
                ]
            )"_json;
            ImModernUI::Alert(attr, size);
        }

        {
            nlohmann::json attr;
            attr["label"] = "##Alert default with no description";
            attr["variant"] = "default";
            attr["icon"] = ICON_POPCORN;
            attr["title"] = "This Alert has a title and an icon. No description.";
            ImModernUI::Alert(attr, size);
        }

        {
            nlohmann::json attr;
            attr["label"] = "##Alert destructive";
            attr["variant"] = "destructive";
            attr["icon"] = ICON_CIRCLE_ALERT;
            attr["title"] = "Unable to process your payment.";
            attr["description"] = R"(
                [
                    {
                        "text": "Please verify your billing information and try again.",
                        "items": [
                            "Check your card details", 
                            "Ensure sufficient funds",
                            "Verify billing address"
                        ]
                    }
                ]
            )"_json;
            ImModernUI::Alert(attr, size);
        }

        ImGui::EndChild();
    }
}