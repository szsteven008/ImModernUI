#include "calendar.h"

#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json_fwd.hpp"
#include "select.h"
#include "themes.h"
#include "nlohmann/json.hpp"
#include <MacTypes.h>
#include <array>
#include <chrono>
#include <format>
#include <string>
#include <tuple>
#include <vector>

namespace ImModernUI {
    using week = std::array<std::chrono::year_month_day, 7>;
    static std::vector<week> year_month_weeks(
        const std::chrono::year_month& ym
    ) {
        std::vector<week> weeks;
        std::chrono::sys_days first { ym / std::chrono::day{1} };
        std::chrono::sys_days last { ym / std::chrono::last };

        std::array<std::chrono::year_month_day, 7> w = {};
        for (auto d=first; 
            d<=last; 
            d += std::chrono::days{1}
        ) {
            std::chrono::year_month_weekday wd {d};
            if ((wd.weekday() == std::chrono::Sunday) && d != first) {
                weeks.push_back(w);
                w = {};
            }
            w[wd.weekday().c_encoding()] = std::chrono::year_month_day{d};
        }
        weeks.push_back(w);

        return weeks;
    }

    static bool calendar_button(
        const std::string& label, 
        bool disabled, 
        float calendar_button_size, 
        bool selected = false, 
        bool icon = false
    ) {
        auto id = ImGui::GetID(label.c_str());

        float w = calendar_button_size;
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, pos.y, 
            pos.x + w, pos.y + w
        };
        ImGui::ItemSize(bb.GetSize());

        bool pressed = false;
        auto draw = ImGui::GetWindowDrawList();
        if (!disabled) {
            ImGui::ItemAdd(bb, id);

            bool hovered = false;
            pressed = ImGui::ButtonBehavior(
                bb, 
                id, 
                &hovered, 
                nullptr
            );

            auto col = 
                ImGui::GetColorU32(
                    selected ? UIThemes::primary() : UIThemes::accent()
                );
            if (hovered || selected) {
                draw->AddRectFilled(
                    bb.Min, 
                    bb.Max, 
                    col, 
                    UISizes::rounded_md()
                );
            }
        }

        if (icon) ImGui::PushFont(UIFont::font_icon());
        auto size = ImGui::CalcTextSize(
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str()), 
            true
        );
        auto col = 
            ImGui::GetColorU32(
                disabled ? UIThemes::muted_foreground() : 
                        UIThemes::accent_foreground()
            );
        if (selected) 
            col = ImGui::GetColorU32(UIThemes::primary_foreground());
        draw->AddText(
            ImVec2(
                (bb.Min.x + bb.Max.x - size.x) * 0.5, 
                (bb.Min.y + bb.Max.y - size.y) * 0.5
            ), 
            col, 
            label.c_str(), 
            ImGui::FindRenderedTextEnd(label.c_str())
        );
        if (icon) ImGui::PopFont();

        return pressed;
    }

    static bool calendar_selected_trigger(
        const std::string& label, 
        const float width
    ) {
        auto& style = ImGui::GetStyle();
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + UISizes::size_8()
        };

        auto id = ImGui::GetID(label.c_str());
        ImGui::ItemAdd(bb, id);
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            nullptr, 
            nullptr
        );

        auto draw = ImGui::GetWindowDrawList();
        ImGui::PushFont(UIFont::font_semibold_sm());
        auto size = ImGui::CalcTextSize(label.c_str());
        float x = bb.Min.x;
        float y = (bb.Min.y + bb.Max.y - size.y) * 0.5;
        draw->AddText(
            ImVec2(x, y), 
            ImGui::GetColorU32(UIThemes::foreground()), 
            label.c_str()
        );
        x += size.x;
        ImGui::PopFont();

        ImGui::PushFont(UIFont::font_icon());
        y = (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5;
        draw->AddText(
            ImVec2(x, y), 
            ImGui::GetColorU32(UIThemes::foreground()), 
            ICON_CHEVRON_DOWN
        );
        ImGui::PopFont();

        return pressed;
    }

    static void calendar_month(
        const std::string label, 
        unsigned& month, 
        const ImVec2& center
    ) {
        const static std::vector<std::tuple<std::string, int>> months {
            {"January", 1}, 
            {"February", 2}, 
            {"March", 3}, 
            {"April", 4}, 
            {"May", 5}, 
            {"June", 6}, 
            {"July", 7}, 
            {"August", 8}, 
            {"September", 9}, 
            {"October", 10}, 
            {"November", 11}, 
            {"December", 12}, 
        };

        std::vector<nlohmann::json> groups;
        std::vector<nlohmann::json> items;

        auto& style = ImGui::GetStyle();
        float width = style.ItemSpacing.x + UISizes::size_4();

        std::string value;
        for (auto& [mon, val]: months) {
            nlohmann::json m;
            m["label"] = mon;
            m["value"] = std::to_string(val);
            items.push_back(m);

            if (month == val) {
                value = std::to_string(val);
                ImGui::PushFont(UIFont::font_regular_sm());
                width += ImGui::CalcTextSize(mon.substr(0, 3).c_str()).x;
                ImGui::PopFont();
            }
        }
        nlohmann::json group;
        group["items"] = items;
        groups.push_back(group);

        nlohmann::json attr;
        attr["label"] = label;
        attr["selected-icon-align"] = "left";
        attr["width"] = width;
        attr["groups"] = groups;

        ImGui::SetCursorPos(
            ImVec2(
                center.x - width - UISizes::m_1(), 
                center.y
            )
        );
        if (ImModernUI::select(
                attr, 
                value, 
                [&](
                    const nlohmann::json& attr, 
                    const std::string& selected_label
                ) {
                    return calendar_selected_trigger(
                        selected_label.substr(0, 3), width
                    );
                }
        )) month = std::stoi(value);
    }

    static void calendar_year(
        const std::string label, 
        const std::chrono::year min_year, 
        const std::chrono::year max_year, 
        int& year, 
        const ImVec2& center
    ) {
        std::vector<nlohmann::json> groups;

        auto& style = ImGui::GetStyle();
        float width = style.ItemSpacing.x + UISizes::size_4();

        std::string value;
        std::vector<nlohmann::json> items;
        for (int i=static_cast<int>(min_year); 
             i<=static_cast<int>(max_year); 
             ++i
        ) {
            std::string val = std::to_string(i);
            nlohmann::json item;
            item["label"] = item["value"] = val;
            items.push_back(item);

            if (year == i) {
                value = item["label"];
                ImGui::PushFont(UIFont::font_regular_sm());
                width += ImGui::CalcTextSize(val.c_str()).x;
                ImGui::PopFont();
            }
        }

        nlohmann::json group;
        group["items"] = items;
        groups.push_back(group);

        nlohmann::json attr;
        attr["label"] = label;
        attr["selected-icon-align"] = "left";
        attr["width"] = width;
        attr["groups"] = groups;
        
        ImGui::SetCursorPos(
            ImVec2(
                center.x + UISizes::m_1(), 
                center.y
            )
        );

        if (ImModernUI::select(
            attr, 
            value, 
            [&](
                const nlohmann::json& attr, 
                const std::string& selected_label
            ) {
                return calendar_selected_trigger(
                    selected_label, width
                );
            }
        )) year = std::stoi(value);
    }

    static void calendar_header(
        std::chrono::year_month& ym, 
        bool year_month_selector, 
        float calendar_button_size
    ) {
        auto max_year = std::chrono::year_month_day {
            std::chrono::floor<std::chrono::days>(
                std::chrono::system_clock::now()
            )
        }.year();
        auto min_year = std::chrono::year(
            static_cast<int>(max_year) - 100
        );

        auto& style = ImGui::GetStyle();
        int x = ImGui::GetContentRegionAvail().x;
        int base_y = UISizes::h_8() * 0.5;

        auto pos = ImGui::GetCursorPos();

        ImGui::SetCursorPos(
            ImVec2(
                pos.x, 
                pos.y + base_y - calendar_button_size * 0.5
            )
        );
        if (calendar_button(
            std::format("{}##left", ICON_CHEVRON_LEFT), 
            ((ym.year() == min_year) && 
                (ym.month() == std::chrono::month{1})), 
            calendar_button_size, 
            false, 
            true
        )) {
            ym -= std::chrono::months{1};
        }

        if (year_month_selector) {
            ImVec2 center { pos.x + x * 0.5f, pos.y };
            unsigned month = static_cast<unsigned>(ym.month());
            calendar_month("##single month", month, center);
            int year = static_cast<int>(ym.year());
            calendar_year("##single year", min_year, max_year, year, center);
            ym = std::chrono::year_month {
                std::chrono::year{year}, 
                std::chrono::month{month}
            };
        } else {
            ImGui::PushFont(UIFont::font_semibold_sm());
            const std::vector<std::string> months {
                "January", "February", "March", "April", 
                "May", "June", "July", "August", 
                "September", "October", "November", "December",  
            };
            std::string ym_str = std::format("{} {}", 
                months[static_cast<unsigned>(ym.month()) - 1], ym.year());
            auto ym_str_size = ImGui::CalcTextSize(ym_str.c_str());
            ImGui::SetCursorPos(
                ImVec2(
                    pos.x + (x - ym_str_size.x) * 0.5, 
                    pos.y + (UISizes::h_8() - ym_str_size.y) * 0.5
                )
            );
            ImGui::TextUnformatted(ym_str.c_str());
            ImGui::PopFont();
        }

        ImGui::SetCursorPos(
            ImVec2(
                pos.x + x - calendar_button_size, 
                pos.y + base_y - calendar_button_size * 0.5
            )
        );
        if (calendar_button(
            std::format("{}##right", ICON_CHEVRON_RIGHT), 
            ((ym.year() == max_year) && 
                (ym.month() == std::chrono::month{12})), 
            calendar_button_size, 
            false, 
            true
        )) {
            ym += std::chrono::months{1};
        }
    }

    static void calendar_week_day_header(
        float calendar_button_size
    ) {
        const std::vector<std::string> week_days {
            "Su", "Mo", "Tu", "We", 
            "Th", "Fr", "Sa"
        };
        for (auto& item: week_days) {
            if (item != week_days.front()) ImGui::SameLine();
            calendar_button(
                item, 
                true, 
                calendar_button_size
            );
        }
    }

    static bool calendar_single_days(
        std::chrono::year_month ym, 
        std::chrono::year_month_day& day, 
        float calendar_button_size
    ) {
        bool changed = false;

        ImGui::BeginGroup();
        auto pos = ImGui::GetCursorPos();
        auto& style = ImGui::GetStyle();
        auto weeks = year_month_weeks(ym);
        for (int i=0; i<weeks.size(); ++i) {
            auto& week = weeks[i];
            float y = pos.y + i * (calendar_button_size + style.ItemSpacing.y);
            for (int j=0; j<week.size(); ++j) {
                auto& d = week[j];
                if (!d.ok()) continue;

                float x = pos.x + j * (calendar_button_size + style.ItemSpacing.x);
                ImGui::SetCursorPos(ImVec2(x, y));

                std::string label = std::format("{}##{}", d.day(), d);
                if (calendar_button(
                    label, 
                    false, 
                    calendar_button_size, 
                    (d == day)
                )) {
                    day = d;
                    changed = true;
                }
            }
        }
        ImGui::EndGroup();

        return changed;
    }

    static bool calendar_single(
        const std::string& label,
        std::chrono::year_month_day& day, 
        bool year_month_selector, 
        float calendar_button_size
    ) {
        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        auto state_storage = ImGui::GetStateStorage();
        unsigned state = state_storage->GetInt(id);
        std::chrono::year_month ui_ym {
            day.year(), day.month()
        };
        if (state) {
            ui_ym = std::chrono::year_month(
                std::chrono::year((state >> 8) & 0xffff), 
                std::chrono::month(state & 0xff)
            );
        }

        auto& style = ImGui::GetStyle();
        int width = style.WindowPadding.x * 2.0; 
        width += calendar_button_size * 7;
        width += style.ItemSpacing.x * 6;

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        flags |= ImGuiChildFlags_Borders;
        if (ImGui::BeginChild(
            label.c_str(), 
            ImVec2(width, 0), 
            flags
        )) {
            calendar_header(
                ui_ym, 
                year_month_selector, 
                calendar_button_size
            );
            calendar_week_day_header(calendar_button_size);
            calendar_single_days(ui_ym, day, calendar_button_size);

            state_storage->SetInt(
                id, 
                ((static_cast<int>(ui_ym.year()) << 8) | 
                    static_cast<unsigned>(ui_ym.month()))
            );
        }

        ImGui::EndChild();
        ImGui::PopID();

        return true;
    }

    static void calendar_range_header(
        std::chrono::year_month& from, 
        std::chrono::year_month& to, 
        float calendar_button_size
    ) {
        auto max_year = std::chrono::year_month_day {
            std::chrono::floor<std::chrono::days>(
                std::chrono::system_clock::now()
            )
        }.year();
        auto min_year = std::chrono::year(
            static_cast<int>(max_year) - 100
        );

        auto& style = ImGui::GetStyle();
        int x = ImGui::GetContentRegionAvail().x;
        int base_y = UISizes::h_8() * 0.5;

        auto pos = ImGui::GetCursorPos();

        ImGui::SetCursorPos(
            ImVec2(
                pos.x, 
                pos.y + base_y - calendar_button_size * 0.5
            )
        );
        if (calendar_button(
            std::format("{}##left", ICON_CHEVRON_LEFT), 
            ((from.year() == min_year) && 
                (from.month() == std::chrono::month{1})), 
            calendar_button_size, 
            false, 
            true
        )) {
            from -= std::chrono::months{1};
            to -= std::chrono::months{1};
        }

        ImGui::PushFont(UIFont::font_semibold_sm());
        const std::vector<std::string> months {
            "January", "February", "March", "April", 
            "May", "June", "July", "August", 
            "September", "October", "November", "December",  
        };
        std::string from_str = std::format("{} {}", 
            months[static_cast<unsigned>(from.month()) - 1], from.year());
        auto from_str_size = ImGui::CalcTextSize(from_str.c_str());
        ImGui::SetCursorPos(
            ImVec2(
                pos.x + (x * 0.5 - style.WindowPadding.x - from_str_size.x) * 0.5, 
                pos.y + base_y - from_str_size.y * 0.5
            )
        );
        ImGui::TextUnformatted(from_str.c_str());

        std::string to_str = std::format("{} {}", 
            months[static_cast<unsigned>(to.month()) - 1], to.year());
        auto to_str_size = ImGui::CalcTextSize(from_str.c_str());
        ImGui::SetCursorPos(
            ImVec2(
                pos.x + x * 0.5 + (x * 0.5 - style.WindowPadding.x - to_str_size.x) * 0.5, 
                pos.y + base_y - to_str_size.y * 0.5
            )
        );
        ImGui::TextUnformatted(to_str.c_str());
        ImGui::PopFont();

        ImGui::SetCursorPos(
            ImVec2(
                pos.x + x - calendar_button_size, 
                pos.y + base_y - calendar_button_size * 0.5
            )
        );
        if (calendar_button(
            std::format("{}##right", ICON_CHEVRON_RIGHT), 
            ((to.year() == max_year) && 
                (to.month() == std::chrono::month{12})), 
            calendar_button_size, 
            false, 
            true
        )) {
            from += std::chrono::months{1};
            to += std::chrono::months{1};
        }        
    }

    static void calendar_range_week_day_header(float calendar_button_size) {
        auto& style = ImGui::GetStyle();
        auto width = ImGui::GetWindowWidth();
        float offset = width * 0.5 + style.WindowPadding.x;

        calendar_week_day_header(calendar_button_size);
        ImGui::SameLine(offset);
        calendar_week_day_header(calendar_button_size);
    }

    static void calendar_range_days(
        const std::chrono::year_month& ui_from, 
        const std::chrono::year_month& ui_to, 
        std::chrono::year_month_day& from, 
        std::chrono::year_month_day& to, 
        float calendar_button_size
    ) {
        auto calendar_days = 
            [&](
                const std::chrono::year_month& ym, 
                std::chrono::year_month_day& from, 
                std::chrono::year_month_day& to
            ) {
                ImGui::BeginGroup();
                auto pos = ImGui::GetCursorPos();
                auto& style = ImGui::GetStyle();
                auto weeks = year_month_weeks(ym);
                auto draw = ImGui::GetWindowDrawList();

                auto screen_pos = ImGui::GetCursorScreenPos();
                float offset_x = calendar_button_size + style.ItemSpacing.x;
                float offset_y = calendar_button_size + style.ItemSpacing.y;
                for (int i=0; i<weeks.size(); ++i) {
                    auto& week = weeks[i];
                    float y = pos.y + i * offset_y;

                    std::vector<int> week_range;
                    for (int j=0; j<week.size(); ++j) {
                        auto& d = week[j];
                        if ((d >= from) && (d <= to)) 
                            week_range.push_back(j);
                    }

                    if (week_range.size() > 1) {
                        auto min = ImVec2(
                            screen_pos.x + week_range.front() * offset_x, 
                            screen_pos.y + i * offset_y
                        );
                        auto max = ImVec2(
                            screen_pos.x + (week_range.back() +1) * offset_x - style.ItemSpacing.x, 
                            min.y + calendar_button_size
                        );
                        draw->AddRectFilled(
                            min, 
                            max, 
                            ImGui::GetColorU32(UIThemes::accent()), 
                            UISizes::rounded_md()
                        );
                    }

                    for (int j=0; j<week.size(); ++j) {
                        auto& d = week[j];
                        if (!d.ok()) continue;

                        float x = pos.x + j * offset_x;
                        ImGui::SetCursorPos(ImVec2(x, y));

                        std::string label = std::format("{}##{}", d.day(), d);
                        if (calendar_button(
                            label, 
                            false, 
                            calendar_button_size, 
                            (d == from) || (d == to)
                        )) {
                            if (d > from && d != to) 
                                to = d; 
                            else if (d < from) 
                                from = d;
                            else if (d == from)
                                from = to;
                            else if (d == to)
                                to = from;
                        }
                    }
                }
                ImGui::EndGroup();
            };

        auto& style = ImGui::GetStyle();
        auto width = ImGui::GetWindowWidth();
        float offset = width * 0.5 + style.WindowPadding.x;

        calendar_days(ui_from, from, to);
        ImGui::SameLine(offset);
        calendar_days(ui_to, from, to);
    }

    static bool calendar_range(
        const std::string& label, 
        std::vector<std::chrono::year_month_day>& days, 
        float calendar_button_size
    ) {
        auto max_year_month = std::chrono::year_month {
            std::chrono::year_month_day {
                std::chrono::floor<std::chrono::days>(
                    std::chrono::system_clock::now()
                )
            }.year() / std::chrono::December
        };

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        auto& from = days[0];
        auto& to = days[1];

        auto ui_from = std::chrono::year_month(
            from.year(), from.month()
        );
        if (ui_from == max_year_month) {
            ui_from = max_year_month - std::chrono::months{1};
        }
        auto ui_to = ui_from + std::chrono::months{1};

        auto state_storage = ImGui::GetStateStorage();
        auto id_from = ImGui::GetID("##range from ID");
        unsigned ui_from_state = state_storage->GetInt(id_from);
        if (ui_from_state) {
            ui_from = std::chrono::year_month {
                std::chrono::year((ui_from_state >> 8) & 0xffff), 
                std::chrono::month(ui_from_state & 0xff)
            };
        }

        auto id_to = ImGui::GetID("##range to ID");
        unsigned ui_to_state = state_storage->GetInt(id_to);
        if (ui_to_state) {
            ui_to = std::chrono::year_month {
                std::chrono::year((ui_to_state >> 8) & 0xffff), 
                std::chrono::month(ui_to_state & 0xff)
            };
        }

        auto& style = ImGui::GetStyle();
        int width = style.WindowPadding.x * 2.0; 
        width += calendar_button_size * 7;
        width += style.ItemSpacing.x * 6;
        width *= 2.0;

        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        flags |= ImGuiChildFlags_Borders;
        if (ImGui::BeginChild(
            label.c_str(), 
            ImVec2(width, 0), 
            flags
        )) {
            calendar_range_header(ui_from, ui_to, calendar_button_size);
            calendar_range_week_day_header(calendar_button_size);
            calendar_range_days(ui_from, ui_to, from, to, calendar_button_size);

            state_storage->SetInt(
                id_from, 
                (static_cast<int>(ui_from.year()) << 8) | 
                    static_cast<unsigned>(ui_from.month())
            );
            state_storage->SetInt(
                id_to, 
                (static_cast<int>(ui_to.year()) << 8) | 
                    static_cast<unsigned>(ui_to.month())
            );
        }

        ImGui::EndChild();
        ImGui::PopID();

        return true;
    }

    bool Calendar(
        const std::string& label, 
        std::vector<std::chrono::year_month_day>& days, /* single: 0 - selected | range: 0-start 1-end */
        bool year_month_selector /* = false */, 
        const std::string size /* = "default" */
    ) {
        float calendar_button_size = 
            (size == "sm") ? UISizes::size_6() : UISizes::size_8();
        ImGui::PushFont(UIFont::font_regular_sm());
        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_FrameBg, UIColors::color_transparent}, 
            {ImGuiCol_Text, UIThemes::foreground()},
            {ImGuiCol_Border, UIThemes::border()},
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }
        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, 
                    ImVec2(UISizes::p_3(), UISizes::p_3())}, 
            {ImGuiStyleVar_ItemSpacing, 
                    ImVec2(0, 0)}, 
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_ChildRounding, UISizes::rounded_md()}, 
            {ImGuiStyleVar_ChildBorderSize, 1.0}
        };
        for (const auto& [idx, val]: style_vars_2) {
            ImGui::PushStyleVar(idx, val);
        }

        if (days.size() > 1) {
            calendar_range(
                label, 
                days, 
                calendar_button_size
            );
        } else {
            calendar_single(
                label, 
                days[0], 
                year_month_selector, 
                calendar_button_size
            );
        }
        
        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());

        ImGui::PopFont();

        return true;
    }

    void ShowCalendarExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild(
            "##Calendar Examples", 
            ImVec2(0, 0), 
            flags
        );

        ImGui::SeparatorText("Basic");
        {
            static std::vector<std::chrono::year_month_day> days {
                std::chrono::year_month_day {
                    std::chrono::floor<std::chrono::days>(
                        std::chrono::system_clock::now()    
                    )
                }
            };

            Calendar(
                "##Calendar", 
                days
            );

            ImGui::SameLine();

            static std::vector<std::chrono::year_month_day> sm_days {
                std::chrono::year_month_day {
                    std::chrono::floor<std::chrono::days>(
                        std::chrono::system_clock::now()    
                    )
                }
            };

            Calendar(
                "##Calendar sm", 
                sm_days, 
                false, 
                "sm"
            );
        }

        ImGui::SeparatorText("Range Calendar");
        {
            static std::chrono::year_month_day to {
                std::chrono::floor<std::chrono::days>(
                    std::chrono::system_clock::now()
                )
            };
            static std::chrono::year_month_day from {
                std::chrono::sys_days{to} - std::chrono::days{30}
            };
            static std::vector<std::chrono::year_month_day> days {
                from, to
            };

            Calendar(
                "##Range Calendar", 
                days
            );

            ImGui::Dummy(ImVec2(0, 0));

            static std::vector<std::chrono::year_month_day> sm_days {
                from, to
            };

            Calendar(
                "##Range Calendar sm", 
                sm_days, 
                false, 
                "sm"
            );
        }
        ImGui::SeparatorText("Calendar: Month and Year Selector");
        {
            static std::vector<std::chrono::year_month_day> days {
                std::chrono::year_month_day {
                    std::chrono::floor<std::chrono::days>(
                        std::chrono::system_clock::now()    
                    )
                }
            };

            Calendar(
                "##Calendar: Month and Year Selector", 
                days, 
                true
            );

            ImGui::SameLine();

            static std::vector<std::chrono::year_month_day> sm_days {
                std::chrono::year_month_day {
                    std::chrono::floor<std::chrono::days>(
                        std::chrono::system_clock::now()    
                    )
                }
            };

            Calendar(
                "##Calendar sm: Month and Year Selector", 
                sm_days, 
                true, 
                "sm"
            );
        }

        ImGui::EndChild();
    }
}