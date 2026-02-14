#include "command.h"

#include "button.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "input-group.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "overlay.h"
#include "separator.h"
#include "themes.h"
#include <format>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace ImModernUI {
    static bool CommandInput(
        const std::string& label,
        const std::string& placeholder, 
        char * buf, 
        int buf_size
    ) {
        return ImModernUI::InputGroup(
            "##Command Input", 
            placeholder, 
            buf, 
            buf_size, 
            false, 
            false, 
            ImVec2(0, 0), 
            "inline", 
            [](float height, char * buf, int buf_size) {
                auto pos = ImGui::GetCursorScreenPos();
                ImGui::SetCursorScreenPos(
                    ImVec2(
                        pos.x, 
                        pos.y + (height - UISizes::text_base()) * 0.5
                    )
                );
                ImGui::PushStyleColor(ImGuiCol_Text, 
                    UIThemes::muted_foreground());
                ImGui::PushFont(UIFont::font_icon());
                ImGui::TextUnformatted(ICON_SEARCH);
                ImGui::PopFont();
                ImGui::PopStyleColor();
            }
        );
    }

    static bool CommandGroup(
        const std::string& label
    ) {
        auto pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(
            ImVec2(
                pos.x + UISizes::p_3(), 
                pos.y
            )
        );

        ImGui::PushStyleColor(ImGuiCol_Text, 
            UIThemes::muted_foreground());
        ImGui::PushFont(UIFont::font_medium_xs());
        ImGui::TextUnformatted(label.c_str());
        ImGui::PopFont();
        ImGui::PopStyleColor();

        return true;
    }

    static bool CommandItem(
        const std::string& label, 
        const std::string& icon, 
        const std::string& shortcut, 
        bool disabled
    ) {
        ImGui::SetCursorPos(
            ImVec2(
                ImGui::GetCursorPosX() + UISizes::p_1(), 
                ImGui::GetCursorPosY() + UISizes::p_1()
            )
        );

        ImVec2 padding(UISizes::p_2(), 1.5f * UISizes::spacing());
        ImVec2 gap(UISizes::m_2(), UISizes::m_2());
        float rounding = UISizes::rounded_sm();

        float width = ImGui::GetContentRegionAvail().x - UISizes::p_1();
        float height = UISizes::size_4() + padding.y * 2.0f;

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };

        auto id = ImGui::GetID(label.c_str());
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered = false, pressed = false;
        if (!disabled) {
            pressed = ImGui::ButtonBehavior(
                bb, 
                id, 
                &hovered, 
                nullptr
            );
        }

        auto draw = ImGui::GetWindowDrawList();
        if (hovered) {
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(UIThemes::accent()), 
                rounding
            );
        }

        auto x = bb.Min.x + padding.x;
        float y = bb.Min.y + padding.y;
        {
            ImGui::PushFont(UIFont::font_icon());
            draw->AddText(
                ImVec2(x, y), 
                ImGui::GetColorU32(UIThemes::muted_foreground()), 
                icon.c_str()
            );
            ImGui::PopFont();
            x += UISizes::size_4() + gap.x;
        }

        {
            ImGui::PushFont(UIFont::font_regular_sm());
            y = (bb.Min.y + bb.Max.y - UISizes::text_sm()) * 0.5;
            auto col = disabled ? 
                UIThemes::muted_foreground() : 
                UIThemes::accent_foreground();
            draw->AddText(
                ImVec2(x, y), 
                ImGui::GetColorU32(col), 
                label.c_str(), 
                ImGui::FindRenderedTextEnd(label.c_str())                
            );
            ImGui::PopFont();
        }

        if (shortcut.size() > 0) {
            ImGui::PushFont(UIFont::font_regular_xs());
            float w = ImGui::CalcTextSize(shortcut.c_str()).x;
            x = bb.Max.x - padding.x - w;
            y = (bb.Min.y + bb.Max.y - UISizes::text_xs()) * 0.5;
            draw->AddText(
                ImVec2(x, y), 
                ImGui::GetColorU32(UIThemes::muted_foreground()), 
                shortcut.c_str(), 
                ImGui::FindRenderedTextEnd(shortcut.c_str())                
            );
            ImGui::PopFont();
        }

        return pressed;
    }

    bool Command(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size, 
        std::function<void(const std::string&)> handler
    ) {
        if (!attr.contains("label") || 
            !attr.contains("groups")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();
        bool dialog = false;
        if (attr.contains("dialog")) 
            dialog = attr["dialog"].get<bool>();
        std::vector<nlohmann::json> groups = 
            attr["groups"].get<std::vector<nlohmann::json>>();

        bool open = Overlay();
        if (!open) return false;

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_WindowBg, UIThemes::popover()}, 
            {ImGuiCol_Text, UIThemes::popover_foreground()}, 
            {ImGuiCol_Border, UIThemes::border()},
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, 
                    ImVec2(0, 0)},
            {ImGuiStyleVar_ItemSpacing, 
                    ImVec2(UISizes::p_1(), UISizes::p_1())},
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_WindowRounding, UISizes::rounded_md()}, 
            {ImGuiStyleVar_ChildRounding, UISizes::rounded_md()}, 
        };
        for (const auto& [idx, var]: style_vars_2) {
            ImGui::PushStyleVar(idx, var);
        }

        ImGui::SetNextWindowSize(size_arg);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
        if (ImGui::Begin(
            label.c_str(), 
            nullptr, 
            flags
        )) {
            auto id = ImGui::GetID(label.c_str());
            ImGui::PushID(id);

            if (dialog) {
                nlohmann::json btn_close;
                btn_close["label"] = "##close";
                btn_close["variant"] = "ghost";
                btn_close["size"] = "icon-sm";
                btn_close["icon"] = ICON_X;
                
                auto x = ImGui::GetContentRegionAvail().x;
                ImVec2 btn_close_size = ImModernUI::CalcButtonSize(btn_close);
                x -= UISizes::p_2() + btn_close_size.x + UISizes::m_2();
                ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
                if (ImGui::BeginChild(
                    "##Dialog", 
                    ImVec2(x, 0), 
                    flags
                )) {
                    CommandInput(label, placeholder, buf, buf_size);
                }
                float h = ImGui::GetWindowHeight();
                ImGui::EndChild();
                ImGui::SameLine();

                ImGui::SetCursorPosY(
                    ImGui::GetCursorPosY() + (h - btn_close_size.y) * 0.5f
                );
                if (ImModernUI::Button(btn_close)) {
                    open = false;
                }
            } else {
                CommandInput(label, placeholder, buf, buf_size);
            }
            ImGui::SetCursorPosY(
                ImGui::GetCursorPosY() - UISizes::p_1()
            );
            ImModernUI::Separator();
            for (auto& group: groups) {
                std::string group_label = group["label"].get<std::string>();
                std::vector<nlohmann::json> items = 
                    group["items"].get<std::vector<nlohmann::json>>();

                CommandGroup(group_label);
                
                for (auto& item: items) {
                    std::string item_label = 
                        item["label"].get<std::string>();
                    std::string item_icon = 
                        item["icon"].get<std::string>();
                    std::string item_shortcut = "";
                    if (item.contains("shortcut")) 
                        item_shortcut = item["shortcut"].get<std::string>();
                    bool disabled = false;
                    if (item.contains("disabled")) 
                        disabled = item["disabled"].get<bool>();
                    if (CommandItem(
                        item_label, 
                        item_icon, 
                        item_shortcut, 
                        disabled
                    )) handler(std::format("{}/{}", group_label, item_label));
                }

                if (group != groups.back()) ImModernUI::Separator();
            }

            ImGui::Dummy(ImVec2(0, UISizes::p_3()));

            ImGui::PopID();
        }

        auto size = ImGui::GetWindowSize();

        ImGui::End();

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());

        auto pos = ImGui::GetCursorScreenPos();
        if (dialog) {
            auto& io = ImGui::GetIO();
            pos.x = (io.DisplaySize.x - size.x) * 0.5f;
            pos.y = (io.DisplaySize.y - size.y) * 0.5f;
        }

        ImGui::SetWindowPos(
            label.c_str(), 
            pos
        );

        return open;
    }

    void ShowCommandExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Command Examples", 
            ImVec2(0, 0), flags);
        
        static bool open = false;
        auto trigger = R"({
                "label": "Open Command Dialog", 
                "variant": "outline"
            })"_json;
        if (ImModernUI::Button(trigger)) {
            open = true;
        }

        if (open) {
            nlohmann::json attr;
            attr["label"] = "##Command Dialog";
            attr["placeholder"] = "Type a command or search...";
            attr["dialog"] = true;

            attr["groups"][0]["label"] = "Suggestions";
            attr["groups"][0]["items"][0]["icon"] = ICON_CALENDAR;
            attr["groups"][0]["items"][0]["label"] = "Calendar";
            attr["groups"][0]["items"][1]["icon"] = ICON_SMILE;
            attr["groups"][0]["items"][1]["label"] = "Search Emoji";
            attr["groups"][0]["items"][2]["icon"] = ICON_CALCULATOR;
            attr["groups"][0]["items"][2]["label"] = "Calculator";
            attr["groups"][0]["items"][2]["disabled"] = true;

            attr["groups"][1]["label"] = "Settings";
            attr["groups"][1]["items"][0]["icon"] = ICON_USER;
            attr["groups"][1]["items"][0]["label"] = "Profile";
            attr["groups"][1]["items"][0]["shortcut"] = "⌘P";
            attr["groups"][1]["items"][1]["icon"] = ICON_CREDIT_CARD;
            attr["groups"][1]["items"][1]["label"] = "Billing";
            attr["groups"][1]["items"][1]["shortcut"] = "⌘B";
            attr["groups"][1]["items"][2]["icon"] = ICON_SETTINGS;
            attr["groups"][1]["items"][2]["label"] = "Settings";
            attr["groups"][1]["items"][2]["shortcut"] = "⌘S";
            std::function<void(const std::string&)> handler = 
                [](const std::string& label) {
                std::cout << label << std::endl;
            };

            static std::vector<char> buf(1024);
            open = Command(
                attr, 
                ImVec2(450, 0), 
                buf.data(), 
                buf.size(), 
                handler
            );
        }
        ImGui::EndChild();
    }
}