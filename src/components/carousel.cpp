#include "carousel.h"

#include "button.h"
#include "card.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <algorithm>
#include <cmath>
#include <format>
#include <functional>
#include <string>

namespace ImModernUI {
    static bool carousel_button(
        std::string label, 
        std::string icon, 
        bool disabled
    ) {
        nlohmann::json attr;
        attr["label"] = label;
        attr["variant"] = "outline";
        attr["shape"] = "circle";
        attr["size"] = "icon";
        attr["icon"] = icon;
        attr["disabled"] = disabled;

        return ImModernUI::Button(attr);
    }

    static bool carousel_horizontal(
        std::function<void(nlohmann::json&)> item, 
        int total, 
        int visible, 
        int * v
    ) {
        ImGui::BeginGroup();
        
        auto pos = ImGui::GetCursorPos();
        auto size = ImGui::GetContentRegionAvail();
        auto gap = ImGui::GetStyle().ItemSpacing;
        float width = size.x - gap.x * 2;

        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x, 
                    pos.y + size.y * 0.5 - UISizes::h_9() * 0.5
                )
            );

            if (carousel_button(
                "Previous", 
                ICON_ARROW_LEFT, 
                (*v == 0)
            )) *v = std::max(0, *v - 1);

            width -= UISizes::w_9();
        }

        ImGui::SameLine();
        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x + size.x - UISizes::w_9(), 
                    pos.y + size.y * 0.5 - UISizes::h_9() * 0.5
                )
            );

            if (carousel_button(
                "Next", 
                ICON_ARROW_RIGHT, 
                (*v == (total - visible))
            )) *v = std::min(total - visible, *v + 1);

            width -= UISizes::w_9();
        }

        ImGui::SameLine();
        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x + (size.x - width) * 0.5, 
                    pos.y
                )
            );

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
                ImVec2(0, 0));
            ImGuiChildFlags flags = ImGuiChildFlags_AlwaysUseWindowPadding;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar;
            window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            ImGui::BeginChild(
                "##content", 
                ImVec2(width, size.y), 
                flags, 
                window_flags
            );

            float item_x = (width - gap.x * (visible - 1)) / visible;
            float item_y = size.y;

            for (int i=0; i<total; ++i) {
                if (i != 0) ImGui::SameLine();
                nlohmann::json attr;
                attr["label"] = std::format("##card.{}", i+1);
                nlohmann::json data;
                data["index"] = i;
                Card(
                    attr, 
                    ImVec2(item_x, item_y), 
                    data, 
                    nullptr, 
                    item, 
                    nullptr
                );
            }

            float current_scroll_x = ImGui::GetScrollX();
            float target_scroll_x = *v * (item_x + gap.x);
            float speed = 12.0f;
            float next = ImLerp(
                current_scroll_x, 
                target_scroll_x, 
                1.0f - expf(-speed * ImGui::GetIO().DeltaTime)
            );

            float diff = next - current_scroll_x;
            if (std::fabsf(diff) < 0.5) next = target_scroll_x;
            ImGui::SetScrollX(next);

            ImGui::PopStyleVar();
            ImGui::EndChild();
        }

        ImGui::EndGroup();

        return true;
    }

    static bool carousel_vertical(
        std::function<void(nlohmann::json&)> item, 
        int total, 
        int visible, 
        int * v
    ) {
        ImGui::BeginGroup();
        
        auto pos = ImGui::GetCursorPos();
        auto size = ImGui::GetContentRegionAvail();
        auto gap = ImGui::GetStyle().ItemSpacing;
        float height = size.y - gap.y * 2;

        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x + size.x * 0.5 - UISizes::h_9() * 0.5, 
                    pos.y
                )
            );

            if (carousel_button(
                "Previous", 
                ICON_ARROW_UP, 
                (*v == 0)
            )) *v = std::max(0, *v - 1);

            height -= UISizes::h_9();
        }

        ImGui::SameLine();
        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x + size.x * 0.5 - UISizes::w_9() * 0.5, 
                    pos.y + size.y - UISizes::h_9()
                )
            );

            if (carousel_button(
                "Next", 
                ICON_ARROW_DOWN, 
                (*v == (total - visible))
            )) *v = std::min(total - visible, *v + 1);

            height -= UISizes::h_9();
        }

        ImGui::SameLine();
        {
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x, 
                    pos.y + (size.y - height) * 0.5
                )
            );

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
                ImVec2(0, 0));
            ImGuiChildFlags flags = ImGuiChildFlags_AlwaysUseWindowPadding;
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar;
            window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            ImGui::BeginChild(
                "##content", 
                ImVec2(size.x, height), 
                flags, 
                window_flags
            );

            float item_x = size.x;
            float item_y = (height - gap.y * (visible - 1)) / visible;

            auto pos_y = ImGui::GetCursorPosY();
            for (int i=0; i<total; ++i) {
                ImGui::SetCursorPosY(pos_y);
                nlohmann::json attr;
                attr["label"] = std::format("##card.{}", i+1);
                nlohmann::json data;
                data["index"] = i;
                Card(
                    attr, 
                    ImVec2(item_x, item_y), 
                    data, 
                    nullptr, 
                    item, 
                    nullptr
                );
                pos_y += item_y + gap.y;
            }

            float current_scroll_y = ImGui::GetScrollY();
            float target_scroll_y = *v * (item_y + gap.y);
            float speed = 12.0f;
            float next = ImLerp(
                current_scroll_y, 
                target_scroll_y, 
                1.0f - expf(-speed * ImGui::GetIO().DeltaTime)
            );

            float diff = next - current_scroll_y;
            if (std::fabs(diff) < 0.5) next = target_scroll_y;
            ImGui::SetScrollY(next);

            ImGui::EndChild();

            ImGui::PopStyleVar();
        }

        ImGui::EndGroup();

        return true;
    }

    bool Carousel(
        const nlohmann::json& attr, 
        std::function<void(nlohmann::json&)> item, 
        int * v
    ) {
        if (!attr.contains("label") || 
            !attr.contains("total")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string orientation = "horizontal";
        if (attr.contains("orientation")) 
            orientation = attr["orientation"].get<std::string>();
        int total = attr["total"].get<int>();
        int visible = 1;
        if (attr.contains("visible")) 
            visible = attr["visible"].get<int>();
        *v = std::min(total - visible, *v);
        *v = std::max(0, *v);

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        if (orientation == "horizontal") 
            carousel_horizontal(item, total, visible, v);
        else if (orientation == "vertical")
            carousel_vertical(item, total, visible, v);

        ImGui::PopID();
        return true;
    }

    void ShowCarouselExamples() {
        auto item = [](nlohmann::json& data) {
            int index = data["index"].get<int>();
            static std::vector<std::string> captions {
                "1", "2", "3", "4", "5" 
            };
            auto size = ImGui::GetWindowSize();
            ImGui::PushFont(UIFont::font_bold_base(), 
                UISizes::text_3xl());
            auto text_size = 
                ImGui::CalcTextSize(captions[index].c_str());
            ImGui::SetCursorPos(
                ImVec2(
                    (size.x - text_size.x) * 0.5, 
                    (size.y - text_size.y) * 0.5
                )
            );
            ImGui::TextUnformatted(captions[index].c_str());
            ImGui::PopFont();
        };

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Carousel Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Horizontal");
        {
            ImGui::BeginChild("##Carousel Horizontal Example", 
                ImVec2(0, UISizes::h_24()));

            static int v = 0;

            nlohmann::json attr;
            attr["label"] = "##Carousel Sizes";
            attr["total"] = 5;
            attr["visible"] = 3;
            Carousel(
                attr, 
                item, 
                &v
            );

            ImGui::EndChild();
        }

        ImGui::SeparatorText("Orientation");
        {
            ImGui::BeginChild("##Carousel Vertical Example", 
                ImVec2(320, 270));

            static int v = 0;

            nlohmann::json attr;
            attr["label"] = "##Carousel Orientation";
            attr["orientation"] = "vertical";
            attr["total"] = 5;
            attr["visible"] = 2;
            Carousel(
                attr, 
                item, 
                &v
            );

            ImGui::EndChild();
        }
        ImGui::EndChild();
    }
}