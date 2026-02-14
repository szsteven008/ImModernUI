#include "toggle-group.h"

#include "global.h"
#include "imgui.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "toggle.h"
#include <string>
#include <vector>

namespace ImModernUI {
    struct ToggleGroupStyle {
        static ImVec2 gap() { return ImVec2(UISizes::m_2(), UISizes::m_2()); }
    };

    bool ToggleGroup(const nlohmann::json& attr, bool * on) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string toggle_group_type = "multiple";
        if (attr.contains("type")) 
            toggle_group_type = attr["type"].get<std::string>();
        std::string variant = "default";
        if (attr.contains("variant")) 
            variant = attr["variant"].get<std::string>();
        std::string size = "default";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        bool spacing = false;
        if (attr.contains("spacing")) 
            spacing = attr["spacing"].get<bool>();
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();
        auto items = 
            attr["items"].get<std::vector<nlohmann::json>>();

        ImGui::PushID(ImGui::GetID(label.c_str()));
        if (spacing) 
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
                ToggleGroupStyle::gap());                
        else 
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
                ImVec2(0, 0));                

        int i = 0, on_idx = -1;
        for (auto& item: items) {
            if (item != items.front()) {
                ImGui::SameLine();
                if (!spacing)
                    ImGui::SetCursorPosX(
                        ImGui::GetCursorPosX() - 1.0
                    );
            }

            nlohmann::json toggle_attr;
            toggle_attr["label"] = item["label"];
            if (item.contains("icon")) 
                toggle_attr["icon"] = item["icon"];
            toggle_attr["variant"] = variant;
            toggle_attr["size"] = size;
            if (disabled) toggle_attr["disabled"] = disabled;
            if (item.contains("on")) 
                toggle_attr["on"] = item["on"];

            if (!spacing) {
                if (item == items.front() && item == items.back())
                    toggle_attr["corner"] = "all";
                if (item == items.front() && item != items.back())
                    toggle_attr["corner"] = "left";
                if (item != items.front() && item == items.back())
                    toggle_attr["corner"] = "right";
                if (item != items.front() && item != items.back())
                    toggle_attr["corner"] = "none";
            }

            if (ImModernUI::Toggle(toggle_attr, &on[i]) && on[i]) {
                on_idx = i;
            }

            i++;
        }
        if (toggle_group_type == "single" && on_idx >= 0) {
            for (int i=0; i<items.size(); ++i) {
                on[i] = false;
                if (i == on_idx) on[i] = true;
            }
        }

        ImGui::PopStyleVar();

        ImGui::PopID();

        return true;
    }

    void ShowToggleGroupExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("Toggle Group Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Outline");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Group 1";
            attr["spacing"] = true;
            attr["items"][0]["label"] = "Star";
            attr["items"][0]["icon"] = "assets/icons/star.svg";
            attr["items"][0]["on"] = "yellow_500";
            attr["items"][1]["label"] = "Heart";
            attr["items"][1]["icon"] = "assets/icons/heart.svg";
            attr["items"][1]["on"] = "red_500";
            attr["items"][2]["label"] = "Bookmark";
            attr["items"][2]["icon"] = "assets/icons/bookmark.svg";
            attr["items"][2]["on"] = "blue_500";

            static bool v[] = {false, false, false};
            ToggleGroup(attr, v);
        }
        ImGui::SeparatorText("Single");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Group 2";
            attr["type"] = "single";
            attr["variant"] = "outline";
            attr["items"][0]["label"] = "##Bold";
            attr["items"][0]["icon"] = ICON_BOLD;
            attr["items"][1]["label"] = "##Italic";
            attr["items"][1]["icon"] = ICON_ITALIC;
            attr["items"][2]["label"] = "##UNDERLINE";
            attr["items"][2]["icon"] = ICON_UNDERLINE;

            static bool v[] = {false, false, false};
            ToggleGroup(attr, v);
        }
        ImGui::SeparatorText("Small");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Group 3";
            attr["type"] = "single";
            attr["variant"] = "outline";
            attr["size"] = "sm";
            attr["items"][0]["label"] = "##Bold";
            attr["items"][0]["icon"] = ICON_BOLD;
            attr["items"][1]["label"] = "##Italic";
            attr["items"][1]["icon"] = ICON_ITALIC;
            attr["items"][2]["label"] = "##UNDERLINE";
            attr["items"][2]["icon"] = ICON_UNDERLINE;

            static bool v[] = {false, false, false};
            ToggleGroup(attr, v);
        }
        ImGui::SeparatorText("Large");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Group 4";
            attr["type"] = "multiple";
            attr["variant"] = "outline";
            attr["size"] = "lg";
            attr["items"][0]["label"] = "##Bold";
            attr["items"][0]["icon"] = ICON_BOLD;
            attr["items"][1]["label"] = "##Italic";
            attr["items"][1]["icon"] = ICON_ITALIC;
            attr["items"][2]["label"] = "##UNDERLINE";
            attr["items"][2]["icon"] = ICON_UNDERLINE;

            static bool v[] = {false, false, false};
            ToggleGroup(attr, v);
        }
        ImGui::SeparatorText("Disabled");
        {
            nlohmann::json attr;
            attr["label"] = "##Toggle Group 5";
            attr["type"] = "multiple";
            attr["variant"] = "outline";
            attr["disabled"] = true;
            attr["items"][0]["label"] = "##Bold";
            attr["items"][0]["icon"] = ICON_BOLD;
            attr["items"][1]["label"] = "##Italic";
            attr["items"][1]["icon"] = ICON_ITALIC;
            attr["items"][2]["label"] = "##UNDERLINE";
            attr["items"][2]["icon"] = ICON_UNDERLINE;

            static bool v[] = {false, false, false};
            ToggleGroup(attr, v);
        }
        ImGui::EndChild();
    }
}