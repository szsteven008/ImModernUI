#include "tabs.h"

#include "card.h"
#include "fonts.h"
#include "global.h"
#include "group.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <format>
#include <functional>
#include <string>
#include <vector>

namespace ImModernUI {
    struct TabsStyle {
        static ImVec4 background() { return UIThemes::muted(); }
        static ImVec4 foreground() { return UIThemes::foreground(); }
        static ImVec4 trigger_activated() { return UIThemes::background(); }
        static ImVec4 trigger_foreground() { 
            if (UIThemes::scheme() == UIThemeScheme::Dark) 
                return UIThemes::muted_foreground();
            return ImVec4(
                UIThemes::foreground().x, 
                UIThemes::foreground().y, 
                UIThemes::foreground().z, 
                0.6
            ); 
        }
        static ImVec4 trigger_hovered_foreground() { 
            return UIThemes::foreground(); 
        }

        static ImVec2 padding() { return ImVec2(3.0, 3.0); }
        static ImVec2 trigger_padding() { 
            return ImVec2(UISizes::p_2(), UISizes::p_1()); 
        }
        static ImVec2 gap() {
            return ImVec2(UISizes::m_2(), UISizes::m_2());
        }
        static ImVec2 trigger_gap() {
            return ImVec2(
                1.5 * UISizes::spacing(), 
                1.5 * UISizes::spacing()
            );
        }

        static float rounding() { return UISizes::rounded_lg(); }
        static float trigger_rounding() { return UISizes::rounded_md(); }

        static ImVec2 trigger_size(
            const std::string& label, 
            bool has_icon
        ) {
            ImGui::PushFont(UIFont::font_medium_sm());
            float x = 2 * TabsStyle::trigger_padding().x;
            float y = UISizes::h_9();

            if (has_icon) x += UISizes::size_4() + TabsStyle::trigger_gap().x;
            x += ImGui::CalcTextSize(label.c_str()).x;

            ImGui::PopFont();

            return ImVec2(x, y);
        }
    };

    static bool tabs_trigger(
        const std::string& variant, 
        const std::string& label, 
        const std::string& icon, 
        const std::string& align, 
        bool disabled, 
        bool selected,
        ImVec2& size
    ) {
        auto id = ImGui::GetID(label.c_str());
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + size.x, 
            pos.y + size.y
        };
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
        if (selected && variant != "line") {
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(TabsStyle::trigger_activated()), 
                TabsStyle::trigger_rounding()
            );
        }

        auto col = ImGui::GetColorU32(
            hovered || selected ? 
                TabsStyle::trigger_hovered_foreground() : 
                TabsStyle::trigger_foreground()
        );
        if (disabled) col = ImGui::GetColorU32(
            ImVec4(
                UIColors::color_black.x, 
                UIColors::color_black.y, 
                UIColors::color_black.z, 
                0.5
            )
        );

        float x = bb.Min.x + TabsStyle::trigger_padding().x;
        if (align == "center") {
            float text_size = ImGui::CalcTextSize(label.c_str()).x;
            if (!icon.empty()) {
                text_size += UISizes::size_4() + TabsStyle::trigger_gap().x;
            }
            x = (bb.Min.x + bb.Max.x - text_size) * 0.5;
        }
        if (!icon.empty()) {
            ImGui::PushFont(UIFont::font_icon());
            draw->AddText(
                ImVec2(
                    x, 
                    (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5
                ), 
                col, 
                icon.c_str()
            );
            ImGui::PopFont();

            x += UISizes::size_4() + TabsStyle::trigger_gap().x;
        }

        auto label_size = ImGui::CalcTextSize(label.c_str());
        float y = (bb.Min.y + bb.Max.y - label_size.y) * 0.5;
        draw->AddText(
            ImVec2(x, y), 
            col, 
            label.c_str()
        );

        if (selected && variant == "line") {
            y += label_size.y;
            draw->AddLine(
                ImVec2(x, y), 
                ImVec2(x + label_size.x, y), 
                col
            );
        }
        
        return pressed;
    }

    bool Tabs(
        const nlohmann::json& attr, 
        int * v, 
        std::function<void(int)> action /* = [](int){} */, 
        float max_width /* = 0 */
    ) {
        if (!attr.contains("label") || 
            !attr.contains("items")) return false;
        auto label = attr["label"].get<std::string>();
        std::string variant = "default";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string orientation = "horizontal";
        if (attr.contains("orientation")) 
            orientation = attr["orientation"].get<std::string>();
        std::string align = "default";
        if (attr.contains("align")) 
            align = attr["align"].get<std::string>();
        auto items = 
            attr["items"].get<std::vector<nlohmann::json>>();

        ImModernUI::BeginGroup();
        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        ImGui::PushFont(UIFont::font_medium_sm());
        float width = 2.0 * TabsStyle::padding().x;
        float height = 2.0 * TabsStyle::padding().y;
        float item_width = 0.0;
        max_width -= 2.0 * TabsStyle::padding().x;
        if (max_width > 0) {
            if (orientation == "horizontal") {
                max_width -= TabsStyle::gap().x * (items.size() - 1);
                item_width = max_width / items.size();
            } else {
                item_width = max_width;
            }
        }

        std::vector<ImVec2> trigger_sizes;
        for (const auto& trigger: items) {
            if (!trigger.contains("name")) continue;
            std::string name = trigger["name"].get<std::string>();
            auto size = TabsStyle::trigger_size(
                name, trigger.contains("icon"));
            size.x = std::max(size.x, item_width);
            trigger_sizes.push_back(size);
            if (orientation == "vertical") {
                width = std::max(width, 
                    size.x + 2.0f * TabsStyle::padding().x);
                if (trigger != items.front()) height += TabsStyle::gap().y;
                height += size.y;
            } else {
                if (trigger != items.front()) width += TabsStyle::gap().x;
                width += size.x;
                height = size.y + 2.0 * TabsStyle::padding().y;
            }
        }

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };

        ImGui::ItemSize(bb.GetSize());
        auto draw = ImGui::GetWindowDrawList();
        if (variant != "line") {
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(TabsStyle::background()), 
                TabsStyle::rounding()
            );
        }

        float x = bb.Min.x + TabsStyle::padding().x;
        float y = bb.Min.y + TabsStyle::padding().y;
        for (int i=0; i<items.size(); ++i) {
            auto& trigger = items[i];
            if (!trigger.contains("name")) continue;
            std::string name = trigger["name"].get<std::string>();
            std::string icon = "";
            if (trigger.contains("icon")) 
                icon = trigger["icon"].get<std::string>();
            bool disabled = false;
            if (trigger.contains("disabled")) 
                disabled = trigger["disabled"].get<bool>();

            ImGui::SetCursorScreenPos(ImVec2(x, y));
            auto& size = trigger_sizes[i];
            if (orientation == "vertical") 
                size.x = bb.GetWidth() - TabsStyle::padding().x * 2;
            if (tabs_trigger(
                variant, 
                name, 
                icon, 
                align, 
                disabled, 
                (*v == i), 
                size
            )) {
                *v = i;
            }

            if (orientation == "vertical") {
                y += size.y + TabsStyle::gap().y;
            } else {
                x += size.x + TabsStyle::gap().x;
            }
        }
        ImGui::PopFont();
        ImGui::PopID();
        action(*v);
        ImModernUI::EndGroup();

        return true;
    }

    void ShowTabsExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Tabs Example", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Usage");
        {
            nlohmann::json attr;
            attr["label"] = "##Tabs Examples: Usage";
            attr["items"] = R"(
            [
                {"name": "Overview"},
                {"name": "Analytics"},
                {"name": "Reports"},
                {"name": "Settings"}
            ]
            )"_json;

            static int val = 0;
            Tabs(
                attr, 
                &val, 
                [](int index) {
                    std::vector<std::array<std::string, 3>> data {
                        {
                            "Overview", 
                            "View your key metrics and recent project activity. "
                            "Track progress across all your active projects.", 
                            "You have 12 active projects and 3 pending tasks."
                        }, 
                        {
                            "Analytics", 
                            "Track performance and user engagement metrics. "
                            "Monitor trends and identify growth opportunities.", 
                            "Page views are up 25% compared to last month."
                        }, 
                        {
                            "Reports", 
                            "Generate and download your detailed reports. "
                            "Export data in multiple formats for analysis.", 
                            "You have 5 reports ready and available to export."
                        }, 
                        {
                            "Settings", 
                            "Manage your account preferences and options. "
                            "Customize your experience to fit your needs.", 
                            "Configure notifications, security, and themes."
                        }, 
                    };

                    nlohmann::json attr;
                    attr["label"] = std::format("Tabs examples: {}", index);
                    attr["title"] = data[index][0];
                    attr["description"] = data[index][1];

                    nlohmann::json d;
                    d["text"] = data[index][2];
                    Card(
                        attr, 
                        ImVec2(400, 0), 
                        d, 
                        nullptr, 
                        [](nlohmann::json& d) {
                            ImGui::PushStyleColor(ImGuiCol_Text, 
                                UIThemes::muted_foreground());
                            std::string text = d["text"].get<std::string>();
                            ImGui::TextWrapped("%s", text.c_str());
                            ImGui::PopStyleColor();
                        }
                    );
                }
            );
        }
        ImGui::SeparatorText("Line");
        {
            nlohmann::json attr;
            attr["label"] = "##Tabs Examples: Line";
            attr["variant"] = "line";
            attr["items"] = R"(
            [
                {"name": "Overview"},
                {"name": "Analytics"},
                {"name": "Reports"}
            ]
            )"_json;

            static int val = 0;
            Tabs(
                attr, 
                &val
            );
        }
        ImGui::SeparatorText("Vertical");
        {
            nlohmann::json attr;
            attr["label"] = "##Tabs Examples: Vertical";
            attr["orientation"] = "vertical";
            attr["items"] = R"(
            [
                {"name": "Account"},
                {"name": "Password"},
                {"name": "Notifications"}
            ]
            )"_json;

            static int val = 0;
            Tabs(
                attr, 
                &val
            );
        }
        ImGui::SeparatorText("Disabled");
        {
            nlohmann::json attr;
            attr["label"] = "##Tabs Examples: Disabled";
            attr["items"] = R"(
            [
                {"name": "Home"}, 
                {"name": "Disabled", "disabled": true}
            ]
            )"_json;

            static int val = 0;
            Tabs(
                attr, 
                &val
            );
        }
        ImGui::SeparatorText("Icons");
        {
            nlohmann::json attr;
            attr["label"] = "##Tabs Examples: Usage";
            attr["items"][0]["name"] = "Preview";
            attr["items"][0]["icon"] = ICON_APP_WINDOW;
            attr["items"][1]["name"] = "Code";
            attr["items"][1]["icon"] = ICON_CODE;

            static int val = 0;
            Tabs(
                attr, 
                &val
            );
        }
        ImGui::EndChild();
    }
}