#include "select.h"

#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "overlay.h"
#include "shadow.h"
#include "themes.h"
#include <algorithm>
#include <string>
#include <vector>

namespace ImModernUI {
    static bool default_select_trigger(
        const nlohmann::json& attr, 
        const std::string& select_label
    ) {
        std::string label = attr["label"].get<std::string>();
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();
        std::string size = "default";
        if (attr.contains("size")) 
            size = attr["size"].get<std::string>();
        float width = attr["width"].get<float>();

        auto id = ImGui::GetID(label.c_str());
        auto height = 
            ((size == "sm") ? UISizes::h_8() : UISizes::h_9());
        auto padding = ImVec2(
            UISizes::p_3(), 
            (height - UISizes::size_4()) * 0.5
        );
        auto rounding = UISizes::rounded_md();
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, pos.y, 
            pos.x + width, pos.y + height
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
        if (select_label.empty()) {
            draw->AddText(
                ImVec2(bb.Min.x + padding.x, bb.Min.y + padding.y), 
                ImGui::GetColorU32(UIThemes::muted_foreground()), 
                placeholder.c_str()
            );
        } else {
            draw->AddText(
                ImVec2(bb.Min.x + padding.x, bb.Min.y + padding.y), 
                ImGui::GetColorU32(UIThemes::foreground()), 
                select_label.c_str()
            );
        }

        ImGui::PushFont(UIFont::font_icon());
        draw->AddText(
            ImVec2(
                bb.Max.x - padding.x - UISizes::size_4(), 
                bb.Min.y + padding.y
            ), 
            ImGui::GetColorU32(UIThemes::muted_foreground()), 
            ICON_CHEVRON_DOWN
        );
        ImGui::PopFont();

        draw->AddRect(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(UIThemes::input()), 
            rounding
        );
        ImModernUI::shadow_xs(
            draw, 
            bb, 
            rounding
        );

        return pressed;
    }

    static bool select_item(
        const std::string& align, 
        const std::string& label, 
        bool selected
    ) {
        auto& style = ImGui::GetStyle();

        auto pos = ImGui::GetCursorScreenPos();
        float width = ImGui::GetContentRegionAvail().x;
        float height = UISizes::size_4() + style.FramePadding.y * 2;

        ImRect bb {
            pos.x, pos.y, 
            pos.x + width, pos.y + height
        };

        ImGui::ItemSize(bb.GetSize());

        auto id = ImGui::GetID(label.c_str());
        ImGui::ItemAdd(bb, id);

        bool hovered;
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            &hovered, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        if (hovered) {
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(UIThemes::accent()), 
                style.FrameRounding
            );
        }

        {
            float x = bb.Min.x + style.FramePadding.x;
            if (align == "left")
                x += UISizes::size_4() + UISizes::m_2();
            auto size = ImGui::CalcTextSize(label.c_str());
            draw->AddText(
                ImVec2(
                    x, 
                    (bb.Min.y + bb.Max.y - size.y) * 0.5
                ), 
                ImGui::GetColorU32(UIThemes::accent_foreground()), 
                label.c_str()
            );
        }

        if (selected) {
            ImGui::PushFont(UIFont::font_icon());
            float x = bb.Max.x - style.FramePadding.x - UISizes::size_4();
            if (align == "left") 
                x = bb.Min.x + style.FramePadding.x;
            draw->AddText(
                ImVec2(
                    x, 
                    (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5
                ), 
                ImGui::GetColorU32(UIThemes::muted_foreground()), 
                ICON_CHECK
            );
            ImGui::PopFont();

            if (ImGui::IsWindowAppearing())
                ImGui::SetScrollHereY();
        }

        return pressed;
    }

    static bool select_content(
        const std::string& selected_icon_align, 
        const nlohmann::json& groups, 
        std::string& value
    ) {
        auto min = ImGui::GetItemRectMin();
        float width = ImGui::GetItemRectSize().x;

        bool open = Overlay();

        if (open) {
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
                    ImVec2(UISizes::p_2(), 1.5f * UISizes::spacing())},
                {ImGuiStyleVar_FramePadding, 
                    ImVec2(UISizes::p_2(), 1.5f * UISizes::spacing())},
                {ImGuiStyleVar_ItemSpacing, 
                    ImVec2(UISizes::m_2(), UISizes::m_2())}, 
            };
            for (const auto& [idx, var]: style_vars_1) {
                ImGui::PushStyleVar(idx, var);
            }

            std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
                {ImGuiStyleVar_WindowBorderSize, 1.0}, 
                {ImGuiStyleVar_WindowRounding, UISizes::rounded_md()}, 
                {ImGuiStyleVar_FrameRounding, UISizes::rounded_md()}, 
            };
            for (const auto& [idx, var]: style_vars_2) {
                ImGui::PushStyleVar(idx, var);
            }

            auto& style = ImGui::GetStyle();
            for (const auto& group: groups) {
                auto items = 
                    group["items"].get<std::vector<nlohmann::json>>();
                for (const auto& item: items) {
                    std::string item_label = item["label"].get<std::string>();
                    auto item_label_x = 
                        ImGui::CalcTextSize(item_label.c_str()).x;
                    width = std::max(
                        width, 
                        item_label_x + style.WindowPadding.x * 2 + 
                        style.FramePadding.x * 2 + style.ItemSpacing.x + 
                        UISizes::size_4()
                    );
                }
            }

            /* calc height*/
            float offset_y = .0f, height = style.WindowPadding.y * 2.0;
            for (auto& group: groups) {
                if (group.contains("label")) {
                    std::string label = group["label"].get<std::string>();
                    ImGui::PushFont(UIFont::font_regular_xs());
                    height += ImGui::CalcTextSize(label.c_str()).y;
                    ImGui::PopFont();
                }
                if (offset_y == .0f) offset_y = height + style.ItemSpacing.y;

                auto items = 
                    group["items"].get<std::vector<nlohmann::json>>();
                for (const auto& item: items) {
                    height += style.ItemSpacing.y;

                    std::string item_value = item["value"].get<std::string>();
                    if (item_value == value) offset_y = height;
                    height += UISizes::size_4() + style.WindowPadding.y * 2;
                }
            }
            
            ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
            flags |= ImGuiWindowFlags_NoResize;
            if (ImGui::Begin("##content", nullptr, flags)) {
                ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
                float scroll_y = ImGui::GetScrollY();
                float y = std::max(
                    min.y - offset_y - scroll_y + style.WindowPadding.y, 
                    0.0f
                );
                ImGui::SetWindowPos(
                    ImVec2(min.x, y)
                );

                auto max_h = ImGui::GetIO().DisplaySize.y;
                height = std::min(max_h - y, height);
                ImGui::SetWindowSize(
                    ImVec2(width, height)
                );

                for (const auto& group: groups) {
                    if (group.contains("label")) {
                        std::string label = group["label"].get<std::string>();
                        ImGui::PushFont(UIFont::font_regular_xs());
                        ImGui::PushStyleColor(
                            ImGuiCol_Text, 
                            ImGui::GetColorU32(UIThemes::muted_foreground())
                        );
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + UISizes::p_2());
                        ImGui::TextUnformatted(label.c_str());
                        ImGui::PopStyleColor();
                        ImGui::PopFont();
                    }

                    auto items = 
                        group["items"].get<std::vector<nlohmann::json>>();
                    for (const auto& item: items) {
                        std::string item_label = item["label"].get<std::string>();
                        std::string item_value = item["value"].get<std::string>();
                        bool selected = (item_value == value);
                        if (selected) offset_y = ImGui::GetCursorPosY();
                        if (select_item(
                                selected_icon_align, 
                                item_label, 
                                selected
                        )) {
                            value = item_value;
                            open = false;
                        }
                    }
                }
            }

            ImGui::End();

            ImGui::PopStyleVar(style_vars_2.size());
            ImGui::PopStyleVar(style_vars_1.size());
            ImGui::PopStyleColor(style_colors.size());
        }

        return open;
    }

    bool select(
        const nlohmann::json& attr, 
        std::string& value, 
        std::function<bool(
            const nlohmann::json&, 
            const std::string&
        )> trigger /* = nullptr */
    ) {
        if (!attr.contains("label") || 
            !attr.contains("groups") || 
            !attr.contains("width")
        ) return false;

        std::string label = attr["label"].get<std::string>();
        std::string selected_icon_align = "right";
        if (attr.contains("selected-icon-align")) 
            selected_icon_align = attr["selected-icon-align"].get<std::string>();
        auto groups = 
            attr["groups"].get<std::vector<nlohmann::json>>();

        auto id = ImGui::GetID(label.c_str());

        auto state_storage = ImGui::GetStateStorage();
        ImGui::PushID(id);
        ImGui::PushFont(UIFont::font_regular_sm());

        std::string select_label = "";
        for (auto& group: groups) {
            auto items = 
                group["items"].get<std::vector<nlohmann::json>>();
            for (auto& item: items) {
                std::string name = item["label"].get<std::string>();
                std::string val = item["value"].get<std::string>();
                if (val == value) select_label = name;
            }
        }

        bool pressed = false;
        if (trigger) 
            pressed = trigger(
                attr, 
                select_label
            );
        else 
            pressed = default_select_trigger(
                attr, 
                select_label
            );
        if (pressed) state_storage->SetBool(id, true);

        if (state_storage->GetBool(id)) {
            if (!select_content(selected_icon_align, groups, value)) {
                state_storage->SetBool(id, false);
            }
        }

        ImGui::PopFont();
        ImGui::PopID();

        return true;
    }

    void ShowSelectExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Select Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Default");
        {
            nlohmann::json attr = R"(
                {
                    "label": "##Select a fruit", 
                    "placeholder": "Select a fruit", 
                    "width": 180.0, 
                    "groups": [
                        {
                            "label": "Fruits", 
                            "items": [
                                {
                                    "label": "Apple", 
                                    "value": "apple"
                                },
                                {
                                    "label": "Banana", 
                                    "value": "banana"
                                },
                                {
                                    "label": "Blueberry", 
                                    "value": "blueberry"
                                },
                                {
                                    "label": "Grapes", 
                                    "value": "grapes"
                                },
                                {
                                    "label": "Pineapple", 
                                    "value": "pineapple"
                                }
                            ]
                        }
                    ]
                }
            )"_json;

            static std::string value;
            ImModernUI::select(attr, value);
        }
        ImGui::SeparatorText("Scrollabel");
        {
            nlohmann::json attr = R"json(
                {
                    "label": "##Select a timezone", 
                    "placeholder": "Select a timezone", 
                    "width": 320.0, 
                    "groups": [
                        {
                            "label": "North America", 
                            "items": [
                                {
                                    "label": "Eastern Standard Time (EST)", 
                                    "value": "est"
                                },
                                {
                                    "label": "Central Standard Time (CST)", 
                                    "value": "cst"
                                },
                                {
                                    "label": "Mountain Standard Time (MST)", 
                                    "value": "mst"
                                },
                                {
                                    "label": "Pacific Standard Time (PST)", 
                                    "value": "pst"
                                },
                                {
                                    "label": "Alaska Standard Time (AKST)", 
                                    "value": "akst"
                                },
                                {
                                    "label": "Hawaii Standard Time (HST)", 
                                    "value": "hst"
                                }
                            ]
                        },
                        {
                            "label": "Europe & Africa", 
                            "items": [
                                {
                                    "label": "Greenwich Mean Time (GMT)", 
                                    "value": "gmt"
                                },
                                {
                                    "label": "Central European Time (CET)", 
                                    "value": "cet"
                                },
                                {
                                    "label": "Eastern European Time (EET)", 
                                    "value": "eet"
                                },
                                {
                                    "label": "Western European Summer Time (WEST)", 
                                    "value": "west"
                                },
                                {
                                    "label": "Central Africa Time (CAT)", 
                                    "value": "cat"
                                },
                                {
                                    "label": "East Africa Time (EAT)", 
                                    "value": "eat"
                                }
                            ]
                        },
                        {
                            "label": "Asia", 
                            "items": [
                                {
                                    "label": "Moscow Time (MSK)", 
                                    "value": "msk"
                                },
                                {
                                    "label": "India Standard Time (IST)", 
                                    "value": "ist"
                                },
                                {
                                    "label": "China Standard Time (CST)", 
                                    "value": "cst_china"
                                },
                                {
                                    "label": "Japan Standard Time (JST)", 
                                    "value": "jst"
                                },
                                {
                                    "label": "Korea Standard Time (KST)", 
                                    "value": "kst"
                                },
                                {
                                    "label": "Indonesia Central Standard Time (WITA)", 
                                    "value": "ist_indonesia"
                                }
                            ]
                        },
                        {
                            "label": "Australia & Pacific", 
                            "items": [
                                {
                                    "label": "Australian Western Standard Time (AWST)", 
                                    "value": "awst"
                                },
                                {
                                    "label": "Australian Central Standard Time (ACST)", 
                                    "value": "acst"
                                },
                                {
                                    "label": "Australian Eastern Standard Time (AEST)", 
                                    "value": "aest"
                                },
                                {
                                    "label": "New Zealand Standard Time (NZST)", 
                                    "value": "nzst"
                                },
                                {
                                    "label": "Fiji Time (FJT)", 
                                    "value": "fjt"
                                }
                            ]
                        },
                        {
                            "label": "South America", 
                            "items": [
                                {
                                    "label": "Argentina Time (ART)", 
                                    "value": "art"
                                },
                                {
                                    "label": "Bolivia Time (BOT)", 
                                    "value": "bot"
                                },
                                {
                                    "label": "Brasilia Time (BRT)", 
                                    "value": "brt"
                                },
                                {
                                    "label": "Chile Standard Time (CLT)", 
                                    "value": "clt"
                                }
                            ]
                        }
                    ]
                }
            )json"_json;

            static std::string value;
            ImModernUI::select(attr, value);
        }
        ImGui::EndChild();
    }

}