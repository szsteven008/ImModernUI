#include "breadcrumb.h"

#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "themes.h"
#include <functional>
#include <string>
#include <vector>
#include <iostream>

namespace ImModernUI {
    static bool breadcrumb_link(
        const std::string& label
    ) {
        auto id = ImGui::GetID(label.c_str());
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        auto pos = ImGui::GetCursorScreenPos();

        ImRect bb {
            pos.x, pos.y, 
            pos.x + label_size.x, pos.y + label_size.y
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered = false;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        auto col = (hovered) ? UIThemes::foreground() : 
            UIThemes::muted_foreground();
        draw->AddText(
            bb.Min, 
            ImGui::GetColorU32(col), 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );
        if (hovered)
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        return pressed;
    }

    static bool breadcrumb_ellipsis(
        const std::string& label
    ) {
        ImGui::PushFont(UIFont::font_icon());

        auto id = ImGui::GetID(label.c_str());
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        auto pos = ImGui::GetCursorScreenPos();

        ImRect bb {
            pos.x, pos.y, 
            pos.x + label_size.x, pos.y + label_size.y
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            nullptr, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        draw->AddText(
            bb.Min, 
            ImGui::GetColorU32(UIThemes::muted_foreground()), 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );

        ImGui::PopFont();
        return pressed;
    }

    static bool breadcrumb_dropdown(
        const std::string& label
    ) {
        auto id = ImGui::GetID(label.c_str());
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        auto pos = ImGui::GetCursorScreenPos();

        const ImVec2 gap {
            UISizes::m_1(), UISizes::m_1()
        };

        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + label_size.x + gap.x + UISizes::size_3(), 
            pos.y + label_size.y
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            nullptr, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        draw->AddText(
            bb.Min, 
            ImGui::GetColorU32(UIThemes::muted_foreground()), 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );
        
        ImGui::PushFont(UIFont::font_icon_sm(), 
            3.5f * UISizes::spacing());
        draw->AddText(
            ImVec2(
                bb.Min.x + label_size.x + gap.x, 
                (bb.Min.y + bb.Max.y - UISizes::size_3()) * 0.5f
            ), 
            ImGui::GetColorU32(UIThemes::muted_foreground()), 
            ICON_CHEVRON_DOWN
        );
        ImGui::PopFont();
        return pressed;
    }

    static bool breadcrumb_page(const std::string& label) {
        auto id = ImGui::GetID(label.c_str());
        auto label_size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );

        auto pos = ImGui::GetCursorScreenPos();

        ImRect bb {
            pos.x, pos.y, 
            pos.x + label_size.x, pos.y + label_size.y
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        bool hovered = false;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        draw->AddText(
            bb.Min, 
            ImGui::GetColorU32(UIThemes::foreground()), 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );

        return pressed;
    }

    static bool breadcrumb_separator(
        const std::string& separator, 
        float height
    ) {
        ImGui::PushFont(UIFont::font_icon_sm(), 
            3.5f * UISizes::spacing());
        ImGui::PushStyleColor(ImGuiCol_Text, 
            ImGui::GetColorU32(UIThemes::muted_foreground()));
        auto pos_y = ImGui::GetCursorPos().y;
        ImGui::SetCursorPosY(pos_y + (height - UISizes::size_3()) * 0.5);
        ImGui::TextUnformatted(separator.c_str());
        ImGui::PopStyleColor();
        ImGui::PopFont();
        return true;
    }

    bool Breadcrumb(
        const nlohmann::json& attr, 
        std::function<void(const std::string&)> action
    ) {
        if (!attr.contains("label") || 
            !attr.contains("items")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string separator = ICON_CHEVRON_RIGHT;
        if (attr.contains("separator")) 
            separator = attr["separator"].get<std::string>();
        auto items = 
            attr["items"].get<std::vector<nlohmann::json>>();

        ImGui::PushFont(UIFont::font_regular_sm());
        ImGui::PushID(ImGui::GetID(label.c_str()));

        float label_size_h = ImGui::CalcTextSize(label.c_str()).y;

        ImVec2 gap {
            1.5f * UISizes::spacing(), 1.5f * UISizes::spacing()
        };
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, gap);

        std::string actived_item = "";
        for (const auto& item: items) {
            if (item != items.front()) {
                ImGui::SameLine();
                breadcrumb_separator(separator, label_size_h);
                ImGui::SameLine();
            }

            std::string item_label = item["label"].get<std::string>();
            if (item == items.back()) {
                breadcrumb_page(item_label);
                break;
            }

            if (!actived_item.empty()) actived_item += "/";
            std::string item_type = "link";
            if (item.contains("type")) 
                item_type = item["type"].get<std::string>();
            bool pressed = false;
            if (item_type == "ellipsis") {
                pressed = breadcrumb_ellipsis(item_label);
                actived_item += "...";
            } else if (item_type == "dropdown") {
                pressed = breadcrumb_dropdown(item_label);
                actived_item += item_label;
            } else {
                pressed = breadcrumb_link(item_label);
                actived_item += item_label;
            }
            if (pressed) action(actived_item);
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopFont();

        return true;
    }

    void ShowBreadcrumbExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Breadcrumb Examples", 
            ImVec2(0, 0), flags);

        ImGui::SeparatorText("Link component");
        {
            nlohmann::json attr;
            attr["label"] = "##Breadcrumb Link component";
            attr["items"][0]["label"] = "Home";
            attr["items"][1]["label"] = "Components";
            attr["items"][2]["label"] = "Breadcrumb";

            Breadcrumb(attr, [](const std::string& actived) {
                std::cout << actived << std::endl;
            });
        }

        ImGui::SeparatorText("Custom separator");
        {
            nlohmann::json attr;
            attr["label"] = "##Breadcrumb Custom separator";
            attr["separator"] = ICON_SLASH;
            attr["items"][0]["label"] = "Home";
            attr["items"][1]["label"] = "Components";
            attr["items"][2]["label"] = "Breadcrumb";

            Breadcrumb(attr, [](const std::string& actived) {
                std::cout << actived << std::endl;
            });
        }

        ImGui::SeparatorText("Dropdown");
        {
            nlohmann::json attr;
            attr["label"] = "##Breadcrumb Dropdown";
            attr["items"][0]["label"] = "Home";
            attr["items"][1]["label"] = "Components";
            attr["items"][1]["type"] = "dropdown";
            attr["items"][2]["label"] = "Breadcrumb";

            Breadcrumb(attr, [](const std::string& actived) {
                std::cout << actived << std::endl;
            });
        }
        
        ImGui::SeparatorText("Collapsed");
        {
            nlohmann::json attr;
            attr["label"] = "##Breadcrumb Collapsed";
            attr["items"][0]["label"] = "Home";
            attr["items"][1]["label"] = ICON_ELLIPSIS;
            attr["items"][1]["type"] = "ellipsis";
            attr["items"][2]["label"] = "Components";
            attr["items"][3]["label"] = "Breadcrumb";

            Breadcrumb(attr, [](const std::string& actived) {
                std::cout << actived << std::endl;
            });
        }
        
        ImGui::EndChild();
    }

}