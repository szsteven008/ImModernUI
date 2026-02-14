#include "imgui_internal.h"
#include "nlohmann/json.hpp"
#include "button.h"

#include "lucide.h"
#include "fonts.h"
#include "global.h"
#include "themes.h"
#include "imgui.h"
#include <format>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

namespace ImModernUI {
    struct ButtonStyle {
        static ImVec4 background(const std::string& variant) {
            if (variant == "primary") return UIThemes::primary();
            if (variant == "outline") 
                return (
                    (UIThemes::current_scheme == UIThemeScheme::Light) ? 
                        UIThemes::background() : 
                        ImVec4(
                            UIThemes::input().x, 
                            UIThemes::input().y,
                            UIThemes::input().z,
                            0.3
                    )
                );
            if (variant == "secondary") return UIThemes::secondary();
            if (variant == "ghost") return UIColors::color_transparent;
            if (variant == "destructive") 
                return (
                    (UIThemes::current_scheme == UIThemeScheme::Light) ? 
                        UIThemes::destructive() : 
                        ImVec4(
                            UIThemes::destructive().x, 
                            UIThemes::destructive().y,
                            UIThemes::destructive().z,
                            0.6
                    )
                );
            if (variant == "link") return UIColors::color_transparent;
            return UIThemes::primary();
        }

        static ImVec4 foreground(const std::string& variant) {
            if (variant == "primary") return UIThemes::primary_foreground();
            if (variant == "outline") return UIThemes::foreground();
            if (variant == "secondary") return UIThemes::secondary_foreground();
            if (variant == "ghost") return UIThemes::foreground();
            if (variant == "destructive") return UIColors::color_white;
            if (variant == "link") return UIThemes::foreground();
            return UIThemes::primary_foreground();
        }

        static ImVec4 hover(const std::string& variant) {
            if (variant == "primary") 
                return ImVec4(
                    UIThemes::primary().x, 
                    UIThemes::primary().y, 
                    UIThemes::primary().z, 
                    0.9
                );
            if (variant == "outline") 
                return (
                    (UIThemes::current_scheme == UIThemeScheme::Light) ? 
                        UIThemes::accent() : 
                        ImVec4(
                            UIThemes::input().x, 
                            UIThemes::input().y,
                            UIThemes::input().z,
                            0.5
                    )
                );
            if (variant == "secondary") 
                return ImVec4(
                    UIThemes::secondary().x, 
                    UIThemes::secondary().y, 
                    UIThemes::secondary().z, 
                    0.8
                );
            if (variant == "ghost") 
                return (
                    (UIThemes::current_scheme == UIThemeScheme::Light) ? 
                        UIThemes::accent() : 
                        ImVec4(
                            UIThemes::accent().x, 
                            UIThemes::accent().y,
                            UIThemes::accent().z,
                            0.5
                    )
                );
            if (variant == "destructive") 
                return ImVec4(
                    UIThemes::destructive().x, 
                    UIThemes::destructive().y, 
                    UIThemes::destructive().z, 
                    0.9
                );            
            if (variant == "link") return UIColors::color_transparent;
            return ImVec4(
                    UIThemes::primary().x, 
                    UIThemes::primary().y, 
                    UIThemes::primary().z, 
                    0.9
                );
        }

        static ImVec4 hover_foreground(const std::string& variant) {
            if (variant == "primary") return UIThemes::primary_foreground();
            if (variant == "outline") return UIThemes::accent_foreground();
            if (variant == "secondary") return UIThemes::secondary_foreground();
            if (variant == "ghost") return UIThemes::accent_foreground();
            if (variant == "destructive") return UIColors::color_white;        
            if (variant == "link") return UIThemes::foreground();
            return UIThemes::primary_foreground();
        }

        static ImVec4 border(const std::string& variant) {
            if (variant == "primary") return UIThemes::border();
            if (variant == "outline") 
                return (
                    (UIThemes::current_scheme == UIThemeScheme::Light) ? 
                        UIThemes::border() : UIThemes::input()
                );
            if (variant == "secondary") return UIThemes::border();
            if (variant == "ghost") return UIThemes::border();
            if (variant == "destructive") return UIThemes::border();        
            if (variant == "link") return UIThemes::border();
            return UIThemes::border();
        }

        static ImVec4 disabled_foreground() {
            return ImVec4(
                UIThemes::foreground().x, 
                UIThemes::foreground().y, 
                UIThemes::foreground().z,
                0.5 
            );
        }

        static ImVec2 padding(const std::string& size, bool has_icon) {
            float x = UISizes::p_4(), y = UISizes::p_2();
            if (size == "xs") {
                x = UISizes::p_2(); y = UISizes::p_2();
                if (has_icon) x = 1.5 * UISizes::spacing();
            } else if (size == "sm") {
                x = UISizes::p_3(); y = UISizes::p_2();
                if (has_icon) x = 2.5 * UISizes::spacing();
            } else if (size == "md") {
                x = UISizes::p_4(); y = UISizes::p_2();
                if (has_icon) x = UISizes::p_3();
            } else if (size == "lg") {
                x = UISizes::p_6(); y = UISizes::p_2();
                if (has_icon) x = UISizes::p_4();
            } else if (size == "icon-xs") {
                x = (UISizes::w_6() - UISizes::size_3()) * 0.5;
                y = (UISizes::h_6() - UISizes::size_3()) * 0.5;
            } else if (size == "icon-sm") {
                x = (UISizes::w_8() - UISizes::size_4()) * 0.5;
                y = (UISizes::h_8() - UISizes::size_4()) * 0.5;
            }
            if (size == "icon") {
                x = (UISizes::w_9() - UISizes::size_4()) * 0.5;
                y = (UISizes::h_9() - UISizes::size_4()) * 0.5;
            }
            if (size == "icon-lg") {
                x = (UISizes::w_10() - UISizes::size_4()) * 0.5;
                y = (UISizes::h_10() - UISizes::size_4()) * 0.5;
            }

            return ImVec2(x, y);
        }

        static ImVec2 gap(const std::string& size) {
            if (size == "xs") 
                return ImVec2(UISizes::spacing(), UISizes::spacing());
            else if (size == "sm") 
                return ImVec2(1.5 * UISizes::spacing(), 1.5 * UISizes::spacing());
            return ImVec2(UISizes::m_2(), UISizes::m_2());
        }

        static float rounding(const std::string& size) {
            (void)size;
            return UISizes::rounded_md();
        }

        static float border_size(const std::string& variant) {
            return ((variant == "outline") ? 1.0 : 0.0);
        }
    
        static ImVec2 CalcButtonSize(
            const std::string& label, 
            const std::string& size, 
            bool has_icon
        ) {
            if (size == "icon-xs") return ImVec2(UISizes::w_6(), UISizes::h_6());
            if (size == "icon-sm") return ImVec2(UISizes::w_8(), UISizes::h_8());
            if (size == "icon") return ImVec2(UISizes::w_9(), UISizes::h_9());
            if (size == "icon-lg") return ImVec2(UISizes::w_10(), UISizes::h_10());

            if (size == "full-sm") return ImVec2(
                ImGui::GetContentRegionAvail().x, 
                UISizes::h_8()
            );
            if (size == "full") return ImVec2(
                ImGui::GetContentRegionAvail().x, 
                UISizes::h_9()
            );
            if (size == "full-lg") return ImVec2(
                ImGui::GetContentRegionAvail().x, 
                UISizes::h_10()
            );

            float width = ButtonStyle::padding(size, has_icon).x * 2;
            if (size == "xs" || size == "icon-xs")
                ImGui::PushFont(UIFont::font_medium_xs());
            else
                ImGui::PushFont(UIFont::font_medium_sm());

            float label_size_x = ImGui::CalcTextSize(
                label.c_str(), 
                ImGui::FindRenderedTextEnd(label.c_str()), 
                true
            ).x;
            ImGui::PopFont();
            width += label_size_x;

            if (has_icon) {
                width += ButtonStyle::gap(size).x;
                if (size == "xs" || size == "icon-xs") 
                    width += UISizes::size_3();
                else 
                    width += UISizes::size_4();   
            }

            if (size == "xs") return ImVec2(width, UISizes::h_6());
            if (size == "sm") return ImVec2(width, UISizes::h_8());
            if (size == "md") return ImVec2(width, UISizes::h_9());
            if (size == "lg") return ImVec2(width, UISizes::h_10());

            return ImVec2(width, UISizes::h_9());
        }
    };

    static bool Button(
        const std::string& label, 
        const std::string& icon, 
        const std::string& icon_align, 
        const std::string& variant, 
        const std::string& size, 
        const std::string& corner,
        bool disabled
    ) {
        bool has_icon = !icon.empty();
        auto button_size = ButtonStyle::CalcButtonSize(
            label, size, has_icon
        );
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + button_size.x, 
            pos.y + button_size.y
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
        auto col = (hovered) ? 
            ImGui::GetColorU32(ButtonStyle::hover(variant)) : 
            ImGui::GetColorU32(ButtonStyle::background(variant));
        ImDrawFlags flags = ImDrawFlags_RoundCornersAll;
        if (corner == "top") flags = ImDrawFlags_RoundCornersTop;
        if (corner == "bottom") flags = ImDrawFlags_RoundCornersBottom;
        if (corner == "left") flags = ImDrawFlags_RoundCornersLeft;
        if (corner == "right") flags = ImDrawFlags_RoundCornersRight;
        if (corner == "none") flags = ImDrawFlags_RoundCornersNone;
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            col, 
            ButtonStyle::rounding(size), 
            flags
        );
        if (ButtonStyle::border_size(variant) > 0) {
            draw->AddRect(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(ButtonStyle::border(variant)), 
                ButtonStyle::rounding(size), 
                flags, 
                ButtonStyle::border_size(variant)
            );
        }

        col = (hovered) ? 
            ImGui::GetColorU32(ButtonStyle::hover_foreground(variant)) : 
            ImGui::GetColorU32(ButtonStyle::foreground(variant));
        if (disabled) col = ImGui::GetColorU32(ButtonStyle::disabled_foreground());

        if (size == "xs" || size == "icon-xs") 
            ImGui::PushFont(UIFont::font_medium_xs());

        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        float offset_x = (bb.Max.x - bb.Min.x - label_size.x) * 0.5;
        if (has_icon) {
            offset_x = ButtonStyle::padding(size, has_icon).x;
            if (icon_align == "left")
                offset_x = bb.Max.x - bb.Min.x - offset_x - label_size.x;
        }
        draw->AddText(
            ImVec2(
                bb.Min.x + offset_x, 
                (bb.Min.y + bb.Max.y - label_size.y) * 0.5
            ), 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );
        if (size == "xs" || size == "icon-xs") 
            ImGui::PopFont();

        if (has_icon) {
            offset_x = ButtonStyle::padding(size, has_icon).x;
            auto icon_size = UISizes::size_4();
            if (size == "xs" || size == "icon-xs") {
                icon_size = UISizes::size_3();
                ImGui::PushFont(UIFont::font_icon_sm());
            } else {
                ImGui::PushFont(UIFont::font_icon());
            }
            if (icon_align == "right") 
                offset_x = bb.Max.x - bb.Min.x - offset_x - icon_size;
            draw->AddText(
                ImVec2(
                    bb.Min.x + offset_x, 
                    (bb.Min.y + bb.Max.y - icon_size) * 0.5
                ), 
                col, 
                icon.c_str()
            );
            ImGui::PopFont();
        }

        return pressed;
    }

    static bool CircleButton(
        const std::string& label, 
        const std::string& icon, 
        const std::string& variant, 
        const std::string& size,
        bool disabled
    ) { 
        auto button_size = ButtonStyle::CalcButtonSize(
            label, size, true
        );
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + button_size.x, 
            pos.y + button_size.y
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

        auto center = ImVec2(
            pos.x + button_size.x * 0.5, 
            pos.y + button_size.y * 0.5
        );
        auto radius = button_size.y * 0.5;

        auto draw = ImGui::GetWindowDrawList();
        auto col = (hovered) ? 
            ImGui::GetColorU32(ButtonStyle::hover(variant)) : 
            ImGui::GetColorU32(ButtonStyle::background(variant));
        draw->AddCircleFilled(
            center, 
            radius, 
            col
        );

        if (ButtonStyle::border_size(variant) > 0) {
            draw->AddCircle(
                center, 
                radius, 
                ImGui::GetColorU32(ButtonStyle::border(variant))
            );
        }

        auto icon_size = UISizes::size_4();
        if (size == "xs" || size == "icon-xs") {
            ImGui::PushFont(UIFont::font_icon_sm());
            icon_size = UISizes::size_3();
        } else
            ImGui::PushFont(UIFont::font_icon());
        col = (hovered) ? 
            ImGui::GetColorU32(ButtonStyle::hover_foreground(variant)) : 
            ImGui::GetColorU32(ButtonStyle::foreground(variant));
        if (disabled) col = ImGui::GetColorU32(ButtonStyle::disabled_foreground());
        draw->AddText(
            ImVec2(
                center.x - icon_size * 0.5, 
                center.y - icon_size * 0.5
            ), 
            col, 
            icon.c_str()
        );
        ImGui::PopFont();

        return pressed;
    }

    static bool LinkButton(
        const std::string& label, 
        const std::string& size, 
        bool disabled
    ) {
        const std::string variant = "link";
        auto button_size = ButtonStyle::CalcButtonSize(
            label, size, false
        );
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + button_size.x, 
            pos.y + button_size.y
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

        if (size == "xs" || size == "icon-xs") 
            ImGui::PushFont(UIFont::font_medium_xs());
        auto draw = ImGui::GetWindowDrawList();
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        float x = bb.Min.x + ButtonStyle::padding(size, false).y;
        float y = bb.Min.y + (bb.Max.y - bb.Min.y - label_size.y) * 0.5;
        auto col = ImGui::GetColorU32(ButtonStyle::foreground(variant));
        if (disabled) col = ImGui::GetColorU32(ButtonStyle::disabled_foreground());
        draw->AddText(
            ImVec2(x, y), 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );
        if (hovered) {
            y = bb.Max.y - (bb.Max.y - bb.Min.y - label_size.y) * 0.5;
            draw->AddLine(
                ImVec2(x, y), 
                ImVec2(x + label_size.x, y), 
                ImGui::GetColorU32(ButtonStyle::foreground(variant))
            );
        }
        if (size == "xs" || size == "icon-xs") 
            ImGui::PopFont();

        return pressed;
    }

    bool Button(const nlohmann::json& attr) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string variant = "primary";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string size = "md";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        std::string shape = "rectangle";
        if (attr.contains("shape")) 
            shape = attr["shape"].get<std::string>();
        std::string icon = "";
        if (attr.contains("icon"))
            icon = attr["icon"].get<std::string>();
        std::string icon_align = "left";
        if (attr.contains("icon-align")) 
            icon_align = attr["icon-align"].get<std::string>();
        std::string corner = "all";
        if (attr.contains("corner")) 
            corner = attr["corner"].get<std::string>();
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();

        ImGui::PushFont(UIFont::font_medium_sm());

        bool pressed = false;
        if (shape == "circle") {
            pressed = CircleButton(
                label, 
                icon, 
                variant, 
                size, 
                disabled
            );
        } else if (variant == "link") {
            pressed = LinkButton(
                label, 
                size, 
                disabled
            );
        } else {
            pressed = Button(
                label, 
                icon, 
                icon_align, 
                variant, 
                size, 
                corner, 
                disabled
            );
        }

        ImGui::PopFont();

        return pressed;
    }

    ImVec2 CalcButtonSize(
        const nlohmann::json& attr
    ) {
        std::string label = attr["label"].get<std::string>();
        std::string size = "md";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        return ButtonStyle::CalcButtonSize(
            label, 
            size, 
            attr.contains("icon") 
        );
    }

    void ShowButtonExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild(
            "Button Examples", 
            ImVec2(0, 0), 
            flags
        );

        std::vector<std::tuple<std::string, std::vector<nlohmann::json>>> buttons {
            {
                    "Primary", 
                    {
                        R"({
                                    "label": "Button##primary xs", 
                                    "variant": "primary", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##primary sm", 
                                    "variant": "primary", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##primary md", 
                                    "variant": "primary", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##primary lg", 
                                    "variant": "primary", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
            {
                    "Outline", 
                    {
                        R"({
                                    "label": "Button##outline xs", 
                                    "variant": "outline", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##outline sm", 
                                    "variant": "outline", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##outline md", 
                                    "variant": "outline", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##outline lg", 
                                    "variant": "outline", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
            {
                    "Secondary", 
                    {
                        R"({
                                    "label": "Button##secondary xs", 
                                    "variant": "secondary", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##secondary sm", 
                                    "variant": "secondary", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##secondary md", 
                                    "variant": "secondary", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##secondary lg", 
                                    "variant": "secondary", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
            {
                    "Ghost", 
                    {
                        R"({
                                    "label": "Button##ghost xs", 
                                    "variant": "ghost", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##ghost sm", 
                                    "variant": "ghost", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##ghost md", 
                                    "variant": "ghost", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##ghost lg", 
                                    "variant": "ghost", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
            {
                    "Destructive", 
                    {
                        R"({
                                    "label": "Button##destructive xs", 
                                    "variant": "destructive", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##destructive sm", 
                                    "variant": "destructive", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##destructive md", 
                                    "variant": "destructive", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##destructive lg", 
                                    "variant": "destructive", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
            {
                    "Link", 
                    {
                        R"({
                                    "label": "Button##link xs", 
                                    "variant": "link", 
                                    "size": "xs"
                                })"_json,
                        R"({
                                    "label": "Button##link sm", 
                                    "variant": "link", 
                                    "size": "sm"
                                })"_json,
                        R"({
                                    "label": "Button##link md", 
                                    "variant": "link", 
                                    "size": "md"
                                })"_json,
                        R"({
                                    "label": "Button##link lg", 
                                    "variant": "link", 
                                    "size": "lg"
                                })"_json,
                    },                     
                },
        };

        for (const auto& [cate, items]: buttons) {
            ImGui::SeparatorText(cate.c_str());
            ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
            ImGui::BeginChild(cate.c_str(), ImVec2(0, 0), flags);
            float y = ImGui::GetCursorPosX();
            for (const auto& item: items) {
                auto size = item["size"].get<std::string>();
                if (size == "xs") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_6()) * 0.5);
                if (size == "sm") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_8()) * 0.5);
                if (size == "md") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_9()) * 0.5);
                if (size == "lg") 
                    ImGui::SetCursorPosY(y);
                if (ImModernUI::Button(item))
                        std::cout << item["label"].get<std::string>() << std::endl;
                if (item != items.back()) ImGui::SameLine();
            }
            ImGui::EndChild();
        }

        std::vector<std::string> cates {
            "primary", "outline", "secondary", "ghost", "destructive"
        };

        ImGui::SeparatorText("Icon");
        ImGui::PushID("Icon Button");
        for (const auto& cate: cates) {
            ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
            ImGui::BeginChild(cate.c_str(), ImVec2(0, 0), flags);
            float y = ImGui::GetCursorPosX();

            std::vector<std::string> sizes {
                "icon-xs", "icon-sm", "icon", "icon-lg"
            };
            for (int i=0; i<sizes.size(); ++i) {
                auto& size = sizes[i];
                if (size == "icon-xs") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_6()) * 0.5);
                if (size == "icon-sm") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_8()) * 0.5);
                if (size == "icon") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_9()) * 0.5);
                if (size == "icon-lg") 
                    ImGui::SetCursorPosY(y);

                nlohmann::json attr;
                attr["label"] = std::format("##{}.{} Icon", 
                    cate, size);
                attr["variant"] = cate;
                attr["size"] = size;
                attr["icon"] = ICON_CIRCLE_FADING_ARROW_UP;

                if (ImModernUI::Button(attr))
                    std::cout << attr["label"].get<std::string>() << std::endl;

                if (i != (cate.size() - 1)) ImGui::SameLine();
            }
            ImGui::EndChild();
        }
        ImGui::PopID();

        ImGui::SeparatorText("With Icon");
        ImGui::PushID("Button With Icon");
        for (const auto& cate: cates) {
            ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
            ImGui::BeginChild(cate.c_str(), ImVec2(0, 0), flags);
            float y = ImGui::GetCursorPosX();

            std::vector<std::string> sizes {
                "xs", "sm", "md", "lg"
            };
            for (int i=0; i<sizes.size(); ++i) {
                auto& size = sizes[i];
                if (size == "xs") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_6()) * 0.5);
                if (size == "sm") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_8()) * 0.5);
                if (size == "md") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_9()) * 0.5);
                if (size == "lg") 
                    ImGui::SetCursorPosY(y);

                nlohmann::json attr;
                attr["label"] = std::format("Button##{} With Icon {}", 
                    cate, size);
                attr["variant"] = cate;
                attr["size"] = size;
                attr["icon"] = ICON_GIT_BRANCH;

                if (ImModernUI::Button(attr))
                    std::cout << attr["label"].get<std::string>() << std::endl;

                if (i != (cate.size() - 1)) ImGui::SameLine();
            }
            ImGui::EndChild();
        }
        ImGui::PopID();

        ImGui::SeparatorText("Rounded");
        ImGui::PushID("Button Rounded");
        for (const auto& cate: cates) {
            ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
            ImGui::BeginChild(cate.c_str(), ImVec2(0, 0), flags);
            float y = ImGui::GetCursorPosX();

            std::vector<std::string> sizes {
                "xs", "sm", "md", "lg"
            };
            for (int i=0; i<sizes.size(); ++i) {
                auto& size = sizes[i];
                if (size == "xs") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_6()) * 0.5);
                if (size == "sm") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_8()) * 0.5);
                if (size == "md") 
                    ImGui::SetCursorPosY(y + 
                        (UISizes::h_10() - UISizes::h_9()) * 0.5);
                if (size == "lg") 
                    ImGui::SetCursorPosY(y);

                nlohmann::json attr;
                attr["label"] = std::format("##{} With Icon {}", 
                    cate, size);
                attr["variant"] = cate;
                attr["size"] = size;
                attr["shape"] = "circle";
                attr["icon"] = ICON_ARROW_UP;

                if (ImModernUI::Button(attr))
                    std::cout << attr["label"].get<std::string>() << std::endl;

                if (i != (cate.size() - 1)) ImGui::SameLine();
            }
            ImGui::EndChild();
        }
        ImGui::PopID();

        ImGui::EndChild();
    }
}