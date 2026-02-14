#include "textarea.h"

#include "button.h"
#include "cache.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "label.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "shadow.h"
#include "themes.h"
#include <algorithm>
#include <cstdint>
#include <format>
#include <string>
#include <vector>
#include <iostream>

namespace ImModernUI {
    struct TextareaStyle {
        static ImVec4 background() {
            if (UIThemes::current_scheme == UIThemeScheme::Dark) 
                return ImVec4(
                    UIThemes::input().x, 
                    UIThemes::input().y, 
                    UIThemes::input().z,
                    0.3 
                );
            return UIColors::color_transparent;
        }

        static ImVec4 foreground() { return UIThemes::foreground(); }
        static ImVec4 placeholder_foreground() {
            return UIThemes::muted_foreground();
        }
        static ImVec4 selection_bg() { return UIThemes::primary(); }
        static ImVec4 selection_foreground() { 
            return UIThemes::primary_foreground(); 
        }
        static ImVec4 border() { return UIThemes::input(); }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_3(), UISizes::p_2()); 
        }
        static ImVec2 gap() { 
            return ImVec2(UISizes::m_2(), UISizes::m_2());
        }
        static float rounding() { return UISizes::rounded_md(); }
    };

    bool Textarea(
        const nlohmann::json& attr, 
        char * buf, 
        int buf_size, 
        std::function<void(char * buf, int buf_size)> action /* = nullptr */, 
        const ImVec2& size /* = ImVec2(0, 0) */
    ) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();
        std::string description = "";
        if (attr.contains("description")) 
            description = attr["description"].get<std::string>();
        std::string action_label = "";
        if (attr.contains("action")) 
            action_label = attr["action"].get<std::string>();
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();

        ImGui::PushID(ImGui::GetID(label.c_str()));
        ImGui::PushFont(UIFont::font_regular_base());
        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_FrameBg, TextareaStyle::background()}, 
            {ImGuiCol_FrameBgHovered, TextareaStyle::background()}, 
            {ImGuiCol_FrameBgActive, TextareaStyle::background()}, 
            {ImGuiCol_Text, UIColors::color_transparent}, 
            {ImGuiCol_Border, TextareaStyle::border()}, 
            {ImGuiCol_TextSelectedBg, UIColors::color_transparent}, 
            {ImGuiCol_InputTextCursor, UIColors::color_transparent}, 
        };
        for (const auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, ImGui::GetColorU32(col));
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_FramePadding, TextareaStyle::padding()}, 
            {ImGuiStyleVar_ItemSpacing, TextareaStyle::gap()}, 
        };
        for (const auto& [idx, val]: style_vars_1) {
            ImGui::PushStyleVar(idx, val);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_FrameRounding, TextareaStyle::rounding()}, 
            {ImGuiStyleVar_FrameBorderSize, 1.0}, 
        };
        for (const auto& [idx, val]: style_vars_2) {
            ImGui::PushStyleVar(idx, val);
        }
        
        if (!label.starts_with("##")) {
            ImModernUI::Label(label.c_str());
        }

        float x = size.x;
        if (x <= 0) x = ImGui::GetContentRegionAvail().x;
        float y = size.y;
        if (y <= 0) y = UISizes::h_16();

        ImGuiInputTextFlags flags = ImGuiInputTextFlags_WordWrap;
        if (disabled) flags |= ImGuiInputTextFlags_ReadOnly;
        bool changed = ImGui::InputTextMultiline(
            label.c_str(), 
            buf, 
            buf_size, 
            ImVec2(x, y), 
            flags 
        );
        if (disabled && (ImGui::IsItemHovered() || ImGui::IsItemActive())) 
            ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);

        auto draw = ImGui::GetWindowDrawList();
        auto min = ImGui::GetItemRectMin();
        auto max = ImGui::GetItemRectMax();

        {
            ImRect bb {
                min, 
                max
            };

            shadow_xs(
                draw, 
                bb, 
                TextareaStyle::rounding()
            );

            if (ImGui::IsItemActive() && !disabled) {
                //ring
                auto col = ImGui::GetColorU32(
                    ImVec4(
                        UIThemes::ring().x, 
                        UIThemes::ring().y, 
                        UIThemes::ring().z, 
                        0.5
                    )
                );
                float thickness = 3.0f;
                draw->AddRect(
                    ImVec2(bb.Min.x - 2.0, bb.Min.y - 2.0), 
                    ImVec2(bb.Max.x + 2.0, bb.Max.y + 2.0), 
                    col, 
                    TextareaStyle::rounding() + thickness, 
                    0, 
                    thickness
                );

                draw->AddRect(
                    bb.Min, 
                    bb.Max, 
                    ImGui::GetColorU32(UIThemes::ring()), 
                    TextareaStyle::rounding()
                );
            }
        }


        auto line_height = ImGui::GetFontSize();
        auto pos = ImVec2(
            min.x + TextareaStyle::padding().x, 
            min.y + TextareaStyle::padding().y
        );

        auto state = 
            ImGui::GetInputTextState(ImGui::GetItemID());

        nlohmann::json cache;
        if (state) {
            cache["line_count"] = state->LineCount;
            cache["sel_start"] = state->GetSelectionStart();
            cache["sel_end"] = state->GetSelectionEnd();
            cache["cursor"] = state->GetCursorPos();
            cache["scroll_y"] = state->Scroll.y;
            cache["offsets"] = state->Ctx->InputTextLineIndex.Offsets;
            cache["end_offset"] = state->Ctx->InputTextLineIndex.EndOffset;

            CacheSet(label, cache);
        } else {
            cache = CacheGet(label);
        }

        if (cache.is_null() || !strlen(buf)) {
            auto col = ImGui::GetColorU32(
                TextareaStyle::placeholder_foreground()
            );
            draw->AddText(
                pos, 
                col, 
                placeholder.c_str()
            );
            if (state && !disabled) {
                bool cursor_is_visible = (state->CursorAnim <= 0.0f) || 
                    ImFmod(state->CursorAnim, 1.20f) <= 0.80f;
                if (ImGui::IsItemActive() && cursor_is_visible) {
                    draw->AddLine(
                        pos, 
                        ImVec2(
                            pos.x, 
                            pos.y + line_height
                        ), 
                        ImGui::GetColorU32(TextareaStyle::foreground())
                    );
                }
            }
        } else {
            int line_count = cache["line_count"].get<int>();
            int sel_start = std::min(
                cache["sel_start"].get<int>(), 
                cache["sel_end"].get<int>()
            );
            int sel_end = std::max(
                cache["sel_start"].get<int>(), 
                cache["sel_end"].get<int>()
            );
            intmax_t cursor = cache["cursor"].get<int>();
            float scroll_y = cache["scroll_y"].get<float>();
            std::vector<int> offsets = cache["offsets"].get<std::vector<int>>();
            int end_offset = cache["end_offset"].get<int>();

            std::vector<std::string> lines(line_count);
            for (int i=0; i<offsets.size(); ++i) {
                int offset = offsets[i];
                if (i == (offsets.size() - 1)) {
                    if (offset != end_offset)
                        lines[i] = std::string(buf + offset);
                    continue;
                }
                int next_offset = offsets[i + 1];
                lines[i] = std::string(buf + offset, 
                    buf + next_offset);
            }

            bool in_selected = false;
            for (int i=0; i<lines.size(); ++i) {
                ImVec2 pos {
                    min.x + TextareaStyle::padding().x, 
                    min.y + TextareaStyle::padding().y + 
                    line_height * i - scroll_y
                };
                if ((pos.y < min.y) || (pos.y > (max.y - line_height))) 
                    continue;
                auto& line = lines[i];
                int line_start = offsets[i];
                int line_end = line_start + line.size();
                int next_start = -1;
                if (i < (lines.size() - 1)) next_start = offsets[i + 1];

                if (state) {
                    bool cursor_is_visible = (state->CursorAnim <= 0.0f) || 
                        ImFmod(state->CursorAnim, 1.20f) <= 0.80f;
                    if (cursor >= line_start && 
                        cursor <= line_end && 
                        cursor != next_start && 
                        cursor_is_visible
                    ) {
                        std::string cursor_text(line.c_str(), cursor - line_start);
                        auto size = ImGui::CalcTextSize(cursor_text.c_str());
                        auto p1 = ImVec2(
                            pos.x + size.x, 
                            pos.y
                        );
                        auto p2 = ImVec2(
                            p1.x, 
                            p1.y + line_height
                        );
                        draw->AddLine(
                            p1, 
                            p2, 
                            ImGui::GetColorU32(TextareaStyle::foreground())
                        );
                    }
                }

                std::string left_text = "";
                std::string sel_text = "";
                std::string right_text = "";

                if (in_selected) {
                    left_text = "";
                    int line_sel_end = line.size();
                    if (sel_end >= line_start && sel_end <= line_end) {
                        line_sel_end = sel_end - line_start;
                        in_selected = false;
                    }
                    sel_text = line.substr(0, line_sel_end);
                    right_text = line.substr(line_sel_end);
                } else {
                    int line_sel_start = line.size();
                    if (sel_start >= line_start && sel_start <= line_end) {
                        in_selected = true;
                        line_sel_start = sel_start - line_start;
                    }
                    left_text = line.substr(0, line_sel_start);
                    int line_sel_end = line.size();
                    if (sel_end >= line_start && sel_end <= line_end) {
                        line_sel_end = sel_end - line_start;
                        in_selected = false;
                    }
                    sel_text = line.substr(line_sel_start, 
                        line_sel_end - line_sel_start);
                    if (line_sel_end < line.size()) {
                        right_text = line.substr(line_sel_end);
                    }
                }

                if (!left_text.empty()) {
                    auto col = disabled ? 
                        ImGui::GetColorU32(UIThemes::muted_foreground()) : 
                        ImGui::GetColorU32(TextareaStyle::foreground());
                    draw->AddText(
                        pos, 
                        col, 
                        left_text.c_str()
                    );
                    pos.x += ImGui::CalcTextSize(left_text.c_str()).x;
                }

                if (!sel_text.empty()) {
                    auto sel_text_size = 
                        ImGui::CalcTextSize(sel_text.c_str());
                    draw->AddRectFilled(
                        pos, 
                        ImVec2(
                            pos.x + sel_text_size.x, 
                            pos.y + line_height
                        ), 
                        ImGui::GetColorU32(TextareaStyle::selection_bg())
                    );
                    auto col = 
                        ImGui::GetColorU32(TextareaStyle::selection_foreground());
                    draw->AddText(
                        pos, 
                        col, 
                        sel_text.c_str()
                    );
                    pos.x += sel_text_size.x;
                }

                if (!right_text.empty()) {
                    auto col = 
                        ImGui::GetColorU32(TextareaStyle::foreground());
                    draw->AddText(
                        pos, 
                        col, 
                        right_text.c_str()
                    );
                }
            }
        }

        if (description.size() > 0) {
            ImGui::PushFont(UIFont::font_regular_sm());
            ImGui::PushStyleColor(ImGuiCol_Text, 
                ImGui::GetColorU32(UIThemes::muted_foreground()));
            ImGui::PushTextWrapPos(
                ImGui::GetCursorScreenPos().x + x);
            ImGui::TextWrapped("%s", description.c_str());
            ImGui::PopTextWrapPos();
            ImGui::PopStyleColor();
            ImGui::PopFont();
        }

        if (action_label.size() > 0) {
            nlohmann::json btn;
            btn["label"] = action_label;
            btn["size"] = "full";
            if (ImModernUI::Button(btn)) action(buf, buf_size);
        }

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();
        ImGui::PopID();

        return changed;
    }

    void ShowTextareaExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        ImGui::BeginChild("##Textarea Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Default");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr;
            attr["label"] = "##Textarea Default";
            attr["placeholder"] = "Type your message here.";

            Textarea(
                attr, 
                buf.data(), 
                buf.size()
            );
        }

        ImGui::SeparatorText("Disabled");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr;
            attr["label"] = "##Textarea Disabled";
            attr["placeholder"] = "Type your message here.";
            attr["disabled"] = true;

            Textarea(
                attr, 
                buf.data(), 
                buf.size()
            );
        }

        ImGui::SeparatorText("With Label");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr;
            attr["label"] = "Your message##Textarea With Label";
            attr["placeholder"] = "Type your message here.";

            Textarea(
                attr, 
                buf.data(), 
                buf.size()
            );
        }

        ImGui::SeparatorText("With Text");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr;
            attr["label"] = "Your message##Textarea With Text";
            attr["placeholder"] = "Type your message here.";
            attr["description"] = "Your message will be copied to the support team.";

            Textarea(
                attr, 
                buf.data(), 
                buf.size()
            );
        }

        ImGui::SeparatorText("With Button");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr;
            attr["label"] = "##Textarea With Button";
            attr["placeholder"] = "Type your message here.";
            attr["action"] = "Send message";

            Textarea(
                attr, 
                buf.data(), 
                buf.size(),
                [](char * buf, int buf_size) {
                    std::cout << std::format("len: {} buf: {}\n", strlen(buf), buf);
                }
            );
        }

        ImGui::EndChild();
    }

}