#include "toggle.h"

#include "fonts.h"
#include "global.h"
#include "image.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include <string>

namespace ImModernUI {
    struct ToggleStyle {
        static ImVec4 background() { return UIColors::color_transparent; }
        static ImVec4 foreground() { return UIThemes::foreground(); }
        static ImVec4 hover() { return UIThemes::muted(); }
        static ImVec4 hover_foreground() { return UIThemes::muted_foreground(); }
        static ImVec4 border() { return UIThemes::input(); }
        static ImVec4 disabled_foreground() {
            return ImVec4(
                UIThemes::foreground().x, 
                UIThemes::foreground().y, 
                UIThemes::foreground().z,
                0.5 
            );
        }

        static ImVec2 padding(const std::string& size) { 
            float x = UISizes::p_2();
            float y = (UISizes::h_9() - UISizes::size_4()) * 0.5;
            if (size == "xs") {
                x = 1.5 * UISizes::spacing();
                y = (UISizes::h_6() - UISizes::size_3()) * 0.5;
            }
            if (size == "sm") {
                x = 1.5 * UISizes::spacing();
                y = (UISizes::h_8() - UISizes::size_4()) * 0.5;
            }
            if (size == "lg") {
                x = 2.5 * UISizes::spacing();
                y = (UISizes::h_10() - UISizes::size_4()) * 0.5;
            }
            return ImVec2(x, y); 
        }
        static ImVec2 gap() { return ImVec2(UISizes::p_2(), UISizes::p_2()); }
        static float rounding() { return UISizes::rounded_md(); }
    };

    bool Toggle(const nlohmann::json& attr, bool * on) {
        if (!attr.contains("label")) return false;

        std::string label = attr["label"].get<std::string>();
        std::string icon = "";
        if (attr.contains("icon")) 
            icon = attr["icon"].get<std::string>();
        std::string variant = "default";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string size = "default";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();
        ImVec4 on_color = UIColors::color_blue_500;
        if (attr.contains("on")) 
            on_color = UIColors::color(attr["on"].get<std::string>());
        std::string corner = "all";
        if (attr.contains("corner")) 
            corner = attr["corner"].get<std::string>();

        ImGui::PushFont(UIFont::font_medium_sm());

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        float icon_size = (size == "xs") ? UISizes::size_3() : UISizes::size_4();
        float height = 
            ToggleStyle::padding(size).y * 2 + icon_size;
        float width = 
            ToggleStyle::padding(size).x * 2  + icon_size;
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        if (label_size.x > 0) {
            width += ToggleStyle::gap().x;
            width += label_size.x;
        } else {
            width = height;
        }

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
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
            if (pressed) *on = !*on;
        }

        auto draw = ImGui::GetWindowDrawList();
        ImDrawFlags flags = ImDrawFlags_RoundCornersAll;
        if (corner == "top") flags = ImDrawFlags_RoundCornersTop;
        if (corner == "bottom") flags = ImDrawFlags_RoundCornersBottom;
        if (corner == "left") flags = ImDrawFlags_RoundCornersLeft;
        if (corner == "right") flags = ImDrawFlags_RoundCornersRight;
        if (corner == "none") flags = ImDrawFlags_RoundCornersNone;
        if (variant != "ghost") {
            draw->AddRect(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(ToggleStyle::border()), 
                ToggleStyle::rounding(), 
                flags
            );
        }
        {
            auto col = (hovered || (*on && variant == "outline")) ? 
                ImGui::GetColorU32(ToggleStyle::hover()) : 
                ImGui::GetColorU32(ToggleStyle::background());
            draw->AddRectFilled(
                ImVec2(bb.Min.x + 1.0, bb.Min.y + 1.0), 
                ImVec2(bb.Max.x - 1.0, bb.Max.y - 1.0), 
                col, 
                ToggleStyle::rounding(), 
                flags
            );
        }
        {
            if (icon.ends_with(".svg")) {
                int w, h;
                auto texture = ImModernUI::load_svg(
                    icon.c_str(), 
                    &w, 
                    &h, 
                    *on, 
                    on_color
                );
                float x = bb.Min.x + ToggleStyle::padding(size).x;
                float y = bb.Min.y + ToggleStyle::padding(size).y;
                if (label_size.x == 0) {
                    x = bb.Min.x + ToggleStyle::padding(size).y;;
                }
                draw->AddImage(
                    texture, 
                    ImVec2(x, y), 
                    ImVec2(x + icon_size, y + icon_size), 
                    ImVec2(0, 0), 
                    ImVec2(1, 1)
                );
            } else {
                ImGui::PushFont(
                    (size == "xs" ? UIFont::font_icon_sm() : UIFont::font_icon()));
                auto col = (hovered) ? 
                    ImGui::GetColorU32(ToggleStyle::hover_foreground()) : 
                    ImGui::GetColorU32(ToggleStyle::foreground());
                if (*on && variant == "default") 
                    col = ImGui::GetColorU32(on_color);
                if (disabled) 
                    col = ImGui::GetColorU32(ToggleStyle::disabled_foreground());
                float x = bb.Min.x + ToggleStyle::padding(size).x;
                float y = bb.Min.y + ToggleStyle::padding(size).y;
                if (label_size.x == 0) {
                    x = bb.Min.x + ToggleStyle::padding(size).y;;
                }
                draw->AddText(
                    ImVec2(x, y), 
                    col, 
                    icon.c_str()
                );
                ImGui::PopFont();
            }
        }

        if (label_size.x > 0) {
            auto col = (hovered) ? 
                ImGui::GetColorU32(ToggleStyle::hover_foreground()) : 
                ImGui::GetColorU32(ToggleStyle::foreground());
            if (disabled) 
                col = ImGui::GetColorU32(ToggleStyle::disabled_foreground());
            float x = bb.Min.x + ToggleStyle::padding(size).x + 
                UISizes::size_4() + ToggleStyle::gap().x;
            float y = (bb.Min.y + bb.Max.y - label_size.y) * 0.5;
            draw->AddText(
                ImVec2(x, y), 
                col, 
                label.c_str(), 
                ImGui::FindRenderedTextEnd(label.c_str())
            );
        }

        ImGui::PopID();
        ImGui::PopFont();

        return pressed;
    }

    void ShowToggleExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("Toggle Examples", 
            ImVec2(0, 0), flags);

        ImGui::SeparatorText("Default");
        {
            nlohmann::json attr;
            attr["label"] = "Bookmark##Toggle Default";
            attr["icon"] = "assets/icons/bookmark.svg";
            attr["on"] = "blue_500";
            static bool on = false;
            Toggle(attr, &on);
        }
        ImGui::SeparatorText("Outline");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Outline";
            attr["icon"] = ICON_ITALIC;
            attr["variant"] = "outline";
            static bool on = false;
            Toggle(attr, &on);
        }
        ImGui::SeparatorText("With Text");
        {
            nlohmann::json attr;
            attr["label"] = "Italic##With Text";
            attr["icon"] = ICON_ITALIC;
            attr["variant"] = "outline";
            static bool on = false;
            Toggle(attr, &on);
        }
        ImGui::SeparatorText("Small");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Small";
            attr["icon"] = ICON_ITALIC;
            attr["variant"] = "outline";
            attr["size"] = "sm";
            static bool on = false;
            Toggle(attr, &on);
        }
        ImGui::SeparatorText("Large");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Large";
            attr["icon"] = ICON_ITALIC;
            attr["variant"] = "outline";
            attr["size"] = "lg";
            static bool on = false;
            Toggle(attr, &on);
        }
        ImGui::SeparatorText("Disabled");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Disabled";
            attr["icon"] = ICON_ITALIC;
            attr["variant"] = "outline";
            attr["disabled"] = true;
            static bool on = false;
            Toggle(attr, &on);
        }
        
        ImGui::EndChild();
    }
}