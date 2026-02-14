#include "alertdialog.h"

#include "button.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "overlay.h"
#include "themes.h"
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

namespace ImModernUI {
    struct AlertDialogStyle {
        static ImVec4 background() { return UIThemes::background(); }
        static ImVec4 foreground() { return UIThemes::foreground(); }
        static ImVec4 overlay() { 
            return ImVec4(
                UIColors::color_black.x, 
                UIColors::color_black.y, 
                UIColors::color_black.z, 
                0.5
            );
        }
        static ImVec4 description() { return UIThemes::muted_foreground(); }
        static ImVec4 border() { return UIThemes::border(); }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_6(), UISizes::p_6()); 
        }
        static ImVec2 gap() { 
            return ImVec2(UISizes::m_4(), UISizes::m_4());
        }

        static float rounding() { return UISizes::rounded_lg(); }
        static float border_size() { return UISizes::border_1(); }
        static float max_width() { return UISizes::w_lg(); }
    };

    bool AlertDialog(
        const nlohmann::json& attr, 
        bool * open
    ) {
        if (!attr.contains("label") || 
            !attr.contains("title")) return false;

        std::string label = attr["label"].get<std::string>();
        std::string title = attr["title"].get<std::string>();
        std::string description = attr["description"].get<std::string>();
        std::string cance_label = "";
        if (attr.contains("cancel")) 
            cance_label = attr["cancel"].get<std::string>();
        std::string action_label = "";
        if (attr.contains("action")) 
            action_label = attr["action"].get<std::string>();

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        ImGui::PushFont(UIFont::font_regular_sm());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_PopupBg, AlertDialogStyle::background()}, 
            {ImGuiCol_Text, AlertDialogStyle::foreground()}, 
            {ImGuiCol_ModalWindowDimBg, AlertDialogStyle::overlay()}, 
            {ImGuiCol_Border, AlertDialogStyle::border()},
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, AlertDialogStyle::padding()},
            {ImGuiStyleVar_FramePadding, AlertDialogStyle::padding()},
            {ImGuiStyleVar_ItemSpacing, AlertDialogStyle::gap()}, 
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_WindowBorderSize, AlertDialogStyle::border_size()}, 
            {ImGuiStyleVar_WindowRounding, AlertDialogStyle::rounding()}, 
        };
        for (const auto& [idx, var]: style_vars_2) {
            ImGui::PushStyleVar(idx, var);
        }

        Overlay(
            ImVec4(
                UIColors::color_black.x, 
                UIColors::color_black.y, 
                UIColors::color_black.z, 
                0.5
            )
        );

        bool action = false;

        ImGui::SetNextWindowFocus();
        auto max_width = ImGui::CalcTextSize(description.c_str()).x;
        max_width += AlertDialogStyle::padding().x * 2;
        if (max_width > AlertDialogStyle::max_width()) 
            max_width = AlertDialogStyle::max_width();
        ImGui::SetNextWindowSize(ImVec2(max_width, 0));
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
        if (ImGui::Begin(label.c_str(), nullptr, flags)) {
            ImGui::PushFont(UIFont::font_semibold_lg());
            ImGui::TextUnformatted(title.c_str());
            ImGui::PopFont();

            float width = ImGui::GetContentRegionAvail().x;
            ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + width);
            ImGui::PushStyleColor(ImGuiCol_Text, AlertDialogStyle::description());
            ImGui::TextUnformatted(description.c_str());
            ImGui::PopStyleColor();
            ImGui::PopTextWrapPos();

            auto pos = ImGui::GetCursorPos();
            float x = pos.x + width;
            float y = pos.y;
            if (!action_label.empty()) {
                nlohmann::json action_button;
                action_button["label"] = action_label;
                action_button["variant"] = "primary";
                action_button["size"] = "sm";
                x -= ImModernUI::CalcButtonSize(action_button).x;
                ImGui::SetCursorPos(ImVec2(x, y));
                if (ImModernUI::Button(action_button)) {
                    *open = false;
                    action = true;
                }
                x -= UISizes::m_2();
            }
            if (!cance_label.empty()) {
                nlohmann::json cancel_button;
                cancel_button["label"] = cance_label;
                cancel_button["variant"] = "outline";
                cancel_button["size"] = "sm";
                x -= ImModernUI::CalcButtonSize(cancel_button).x;
                ImGui::SetCursorPos(ImVec2(x, y));
                if (ImModernUI::Button(cancel_button)) {
                    *open = false;
                }
            }

            auto& display_size = ImGui::GetIO().DisplaySize;
            auto size = ImGui::GetWindowSize();
            ImGui::SetWindowPos(
                ImVec2(
                    (display_size.x - size.x) * 0.5, 
                    (display_size.y - size.y) * 0.5
                )
            );

            ImGui::End();
        }

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());

        ImGui::PopFont();
        ImGui::PopID();

        return action;
    }

    void ShowAlertDialogExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("AlertDialog Examples", 
            ImVec2(0, 0), flags);
        {
            nlohmann::json attr = R"(
                {
                    "label": "alert dialog",
                    "title": "Are you absolutely sure?", 
                    "description": "This action cannot be undone. This will permanently delete your account and remove your data from our servers.",
                    "cancel": "Cancel", 
                    "action": "Continue"
                }
            )"_json;

            static bool show_alert_dialog = false;
            if (show_alert_dialog) 
                if (AlertDialog(attr, &show_alert_dialog)) {
                    std::cout << "Continue..." << std::endl;
                }

            nlohmann::json trigger = R"(
                {
                    "label": "Show Dialog", 
                    "variant": "outline", 
                    "size": "sm"
                }
            )"_json;
            if (ImModernUI::Button(trigger)) show_alert_dialog = true;
        }
        ImGui::EndChild();
    }
}