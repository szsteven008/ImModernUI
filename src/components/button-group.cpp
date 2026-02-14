#include "button-group.h"

#include "button.h"
#include "imgui.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <string>
#include <iostream>

namespace ImModernUI {
    bool ButtonGroup(
        const nlohmann::json& attr, 
        std::function<void(const std::string&)> action
    ) {
        if (!attr.contains("label") || 
            !attr.contains("buttons")) return false;

        std::string label = attr["label"].get<std::string>();
        std::string size = "md";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        std::string orientation = "horizontal";
        if (attr.contains("orientation")) 
            orientation = attr["orientation"].get<std::string>();
        auto buttons = attr["buttons"];

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);
        ImGui::BeginGroup();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        auto pos = ImGui::GetCursorPos();
        for (auto& button: buttons) {
            if (button != buttons.front()) {
                if (orientation == "vertical") {
                    ImGui::SetCursorPosY(pos.y - 1.0);
                } else {
                    ImGui::SameLine();
                    ImGui::SetCursorPosX(pos.x - 1.0);
                }
            }

            if (!button.contains("label") || 
                !button.contains("value")) continue;

            auto button_label = button["label"].get<std::string>();
            std::string button_type = "text";
            if (button.contains("type")) 
                button_type = button["type"].get<std::string>();
            std::string button_value = button["value"].get<std::string>();

            nlohmann::json button_attr;
            if (button_type == "text") {
                button_attr["label"] = button_label;
                button_attr["size"] = size;
            } else {
                button_attr["label"] = "## " + button_label;
                button_attr["icon"] = button_label;
                if (size == "sm") button_attr["size"] = "icon-sm";
                else if (size == "md") button_attr["size"] = "icon";
                else if (size == "lg") button_attr["size"] = "icon-lg";
            }
            button_attr["variant"] = "outline";
            button_attr["corner"] = "none";
            if (button == buttons.front() && 
                button != buttons.back()) {
                if (orientation == "vertical") 
                    button_attr["corner"] = "top";
                else
                    button_attr["corner"] = "left";
            }
            if (button != buttons.front() && 
                button == buttons.back()) {
                if (orientation == "vertical") 
                    button_attr["corner"] = "bottom";
                else
                    button_attr["corner"] = "right";
            }
            if (button == buttons.front() && 
                button == buttons.back()) 
                button_attr["corner"] = "all";

            bool pressed = ImModernUI::Button(button_attr);
            if (pressed) action(button_value);

            auto button_size = ImGui::GetItemRectSize();
            if (orientation == "vertical")
                pos.y = pos.y + button_size.y - 1.0;
            else
                pos.x = pos.x + button_size.x - 1.0;
        }
        ImGui::PopStyleVar();

        ImGui::EndGroup();
        ImGui::PopID();

        return true;
    }

    void ShowButtonGroupExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Button Group Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Orientation");
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Orientation";
            attr["orientation"] = "vertical";
            attr["buttons"][0]["label"] = ICON_PLUS;
            attr["buttons"][0]["type"] = "icon";
            attr["buttons"][0]["value"] = "0";
            attr["buttons"][1]["label"] = ICON_MINUS;
            attr["buttons"][1]["type"] = "icon";
            attr["buttons"][1]["value"] = "1";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }
        ImGui::SeparatorText("Size");
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Size Small";
            attr["size"] = "sm";
            attr["buttons"][0]["label"] = "Small";
            attr["buttons"][0]["value"] = "0";
            attr["buttons"][1]["label"] = "Button";
            attr["buttons"][1]["value"] = "1";
            attr["buttons"][2]["label"] = "Group";
            attr["buttons"][2]["value"] = "2";
            attr["buttons"][3]["label"] = ICON_PLUS;
            attr["buttons"][3]["type"] = "icon";
            attr["buttons"][3]["value"] = "3";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Size Default";
            attr["size"] = "md";
            attr["buttons"][0]["label"] = "Default";
            attr["buttons"][0]["value"] = "0";
            attr["buttons"][1]["label"] = "Button";
            attr["buttons"][1]["value"] = "1";
            attr["buttons"][2]["label"] = "Group";
            attr["buttons"][2]["value"] = "2";
            attr["buttons"][3]["label"] = ICON_PLUS;
            attr["buttons"][3]["type"] = "icon";
            attr["buttons"][3]["value"] = "3";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Size Large";
            attr["size"] = "lg";
            attr["buttons"][0]["label"] = "Large";
            attr["buttons"][0]["value"] = "0";
            attr["buttons"][1]["label"] = "Button";
            attr["buttons"][1]["value"] = "1";
            attr["buttons"][2]["label"] = "Group";
            attr["buttons"][2]["value"] = "2";
            attr["buttons"][3]["label"] = ICON_PLUS;
            attr["buttons"][3]["type"] = "icon";
            attr["buttons"][3]["value"] = "3";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }
        ImGui::SeparatorText("Nested");
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Nested 1";
            attr["size"] = "sm";
            attr["buttons"][0]["label"] = "1";
            attr["buttons"][0]["value"] = "1";
            attr["buttons"][1]["label"] = "2";
            attr["buttons"][1]["value"] = "2";
            attr["buttons"][2]["label"] = "3";
            attr["buttons"][2]["value"] = "3";
            attr["buttons"][3]["label"] = "4";
            attr["buttons"][3]["value"] = "4";
            attr["buttons"][4]["label"] = "5";
            attr["buttons"][4]["value"] = "5";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }
        ImGui::SameLine();
        {
            nlohmann::json attr;
            attr["label"] = "Button Group: Nested 2";
            attr["size"] = "sm";
            attr["buttons"][0]["label"] = ICON_ARROW_LEFT;
            attr["buttons"][0]["type"] = "icon";
            attr["buttons"][0]["value"] = "0";
            attr["buttons"][1]["label"] = ICON_ARROW_RIGHT;
            attr["buttons"][1]["type"] = "icon";
            attr["buttons"][1]["value"] = "1";

            ButtonGroup(attr, [](const std::string& value) {
                std::cout << value << std::endl;
            });
        }

        ImGui::EndChild();
    }
}