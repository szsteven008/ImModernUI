#include "input.h"

#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "nfd.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "shadow.h"
#include "themes.h"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <format>
#include <string>
#include <vector>

namespace ImModernUI {
    struct InputStyle {
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
            return ImVec2(UISizes::p_3(), UISizes::p_1()); 
        }
        static ImVec2 gap() { 
            return ImVec2(UISizes::m_2(), UISizes::m_2());
        }
        static float rounding() { return UISizes::rounded_md(); }
    };

    static bool input_default(        
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size
    ) {
        std::string label = attr["label"].get<std::string>();
        std::string input_type = "text";
        if (attr.contains("type")) 
            input_type = attr["type"].get<std::string>();
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();
        bool border = true;
        if (attr.contains("border")) 
            border = attr["border"].get<bool>();

        ImGui::PushFont(UIFont::font_regular_base());
        float label_size_h = ImGui::CalcTextSize(
                label.c_str()
            ).y;

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_FrameBg, 
                (disabled && border ? 
                    ImVec4(
                        InputStyle::background().x, 
                        InputStyle::background().y, 
                        InputStyle::background().z, 
                        0.1
                    ) 
                    : InputStyle::background())}, 
            {ImGuiCol_FrameBgHovered, InputStyle::background()}, 
            {ImGuiCol_FrameBgActive, InputStyle::background()}, 
            {ImGuiCol_Text, 
                ((input_type == "invalid") ? 
                    UIThemes::destructive() : InputStyle::foreground())}, 
            {ImGuiCol_Border, 
                (border ? ((input_type == "invalid") ? 
                                UIThemes::destructive() : InputStyle::border()
                            ) : UIColors::color_transparent)}, 
            {ImGuiCol_TextSelectedBg, InputStyle::selection_bg()}, 
            {ImGuiCol_InputTextCursor, InputStyle::foreground()}, 
        };
        for (const auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, ImGui::GetColorU32(col));
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_FramePadding, 
                    ImVec2(
                        (border ? InputStyle::padding().x : 0.0), 
                        (size_arg.y - label_size_h) * 0.5
                    )
                }, 
            {ImGuiStyleVar_ItemSpacing, InputStyle::gap()}, 
        };
        for (const auto& [idx, val]: style_vars_1) {
            ImGui::PushStyleVar(idx, val);
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_FrameRounding, InputStyle::rounding()}, 
            {ImGuiStyleVar_FrameBorderSize, 1.0}, 
        };
        for (const auto& [idx, val]: style_vars_2) {
            ImGui::PushStyleVar(idx, val);
        }

        bool changed = false;
        ImGui::SetNextItemWidth(size_arg.x);
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
        if (input_type == "password") flags |= ImGuiInputTextFlags_Password;
        ImGui::BeginDisabled(disabled);
        changed = ImGui::InputTextWithHint(
            std::format("##{}", label).c_str(), 
            placeholder.c_str(), 
            buf, 
            buf_size, 
            flags
        );
        ImGui::EndDisabled();
        auto state = 
            ImGui::GetInputTextState(ImGui::GetItemID());
        if (state && state->HasSelection()) {
            int start = std::min(state->GetSelectionStart(), 
                state->GetSelectionEnd());
            int end = std::max(state->GetSelectionStart(), 
                state->GetSelectionEnd());

            std::string select_text(buf + start, end - start);
            std::string left_text(buf, buf + start);

            auto left_text_size = ImGui::CalcTextSize(
                left_text.c_str()
            );

            auto min = ImGui::GetItemRectMin();
            auto max = ImGui::GetItemRectMax();

            auto draw = ImGui::GetWindowDrawList();
            float x = min.x + left_text_size.x + 
                (border ? InputStyle::padding().x : 0) - state->Scroll.x;
            float y = (min.y + max.y - left_text_size.y) * 0.5;
            draw->AddText(
                ImVec2(x, y), 
                ImGui::GetColorU32(InputStyle::selection_foreground()), 
                select_text.c_str()
            );
        }

        if (border) {
            auto min = ImGui::GetItemRectMin();
            auto max = ImGui::GetItemRectMax();
            auto draw = ImGui::GetWindowDrawList();
            ImRect bb {
                min, max
            };

            shadow_xs(
                draw, 
                bb, 
                InputStyle::rounding()
            );

            if (ImGui::IsItemActive()) {
                ImVec4 ring = (input_type == "invalid") ? 
                    UIThemes::destructive() : UIThemes::ring();
                //ring
                auto col = ImGui::GetColorU32(
                    ImVec4(
                        ring.x, 
                        ring.y, 
                        ring.z, 
                        (input_type == "invalid") ? 0.2 : 0.5
                    )
                );
                float thickness = 3.0f;
                draw->AddRect(
                    ImVec2(bb.Min.x - 2.0, bb.Min.y - 2.0), 
                    ImVec2(bb.Max.x + 2.0, bb.Max.y + 2.0), 
                    col, 
                    InputStyle::rounding() + thickness, 
                    0, 
                    thickness
                );

                draw->AddRect(
                    bb.Min, 
                    bb.Max, 
                    ImGui::GetColorU32(ring), 
                    InputStyle::rounding()
                );
            }
        }

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();

        return changed;
    }

    static bool input_file(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size
    ) {
        std::string label = attr["label"].get<std::string>();
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();
        if (!strlen(buf)) {
            strcpy(buf, placeholder.c_str());
        }
        bool disabled = false;
        if (attr.contains("disabled")) 
            disabled = attr["disabled"].get<bool>();

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + size_arg.x, 
            pos.y + size_arg.y
        };
        ImGui::ItemSize(bb.GetSize());

        auto id = ImGui::GetID(label.c_str());
        ImGui::BeginDisabled(disabled);
        ImGui::ItemAdd(bb, id);
        bool pressed = ImGui::ButtonBehavior(
            bb, 
            id, 
            nullptr, 
            nullptr
        );
        ImGui::EndDisabled();

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(
            (disabled ? 
                    ImVec4(
                        InputStyle::background().x, 
                        InputStyle::background().y, 
                        InputStyle::background().z, 
                        0.1
                    ) 
                    : InputStyle::background())
                ), 
            InputStyle::rounding()
        );
        draw->AddRect(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(InputStyle::border()), 
            InputStyle::rounding()
        );

        shadow_xs(
            draw, 
            bb, 
            InputStyle::rounding()
        );

        float x = bb.Min.x + InputStyle::padding().x;
        float y = (bb.Min.y + bb.Max.y) * 0.5;
        {
            ImGui::PushFont(UIFont::font_bold_sm());
            const char * hint = "Choose a file";
            auto size = ImGui::CalcTextSize(hint);

            draw->AddText(
                ImVec2(x, y - size.y * 0.5), 
                ImGui::GetColorU32(
                    (disabled ? 
                        InputStyle::placeholder_foreground() : 
                        InputStyle::foreground()
                    )
                ), 
                hint
            );

            ImGui::PopFont();

            x += size.x;
            x += InputStyle::padding().x;
        }

        {
            auto size = ImGui::CalcTextSize(buf);
            draw->AddText(
                ImVec2(x, y - size.y * 0.5), 
                ImGui::GetColorU32(
                    (disabled ? 
                        InputStyle::placeholder_foreground() : 
                        InputStyle::foreground()
                    )
                ), 
                buf
            );
        }

        return pressed;
    }

    bool Input(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size
    ) {
        if (!attr.contains("label")) return false;
        std::string input_type = "text";
        if (attr.contains("type")) 
            input_type = attr["type"].get<std::string>();

        float x = (size_arg.x > 0) ? 
            size_arg.x : ImGui::GetContentRegionAvail().x;
        float y = (size_arg.y > 0) ? 
            size_arg.y : UISizes::h_9();

        bool changed = false;

        if (input_type == "file") {
            changed = input_file(
                attr, 
                ImVec2(x, y), 
                buf, 
                buf_size
            );
        } else {
            changed = input_default(
                attr, 
                ImVec2(x, y), 
                buf, 
                buf_size
            );
        }

        return changed;
    }

    void ShowInputExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        ImGui::BeginChild("##Input Examples", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Basic");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr = R"(
                {
                    "label": "Input Basic", 
                    "placeholder": "Enter text"
                }
            )"_json;
            Input(
                attr, 
                ImVec2(0, 0), 
                buf.data(), 
                buf.size()
            );
        }
        ImGui::SeparatorText("File");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr = R"(
                {
                    "label": "Input File", 
                    "type": "file", 
                    "placeholder": "No file chosen"
                }
            )"_json;
            if (Input(
                attr, 
                ImVec2(0, 0), 
                buf.data(), 
                buf.size()
            )) {
                nfdchar_t * out_path= nullptr;
                nfdresult_t result = NFD_OpenDialog(
                    &out_path, 
                    nullptr, 
                    0, 
                    "."
                );
                if (result == NFD_OKAY) {
                    std::filesystem::path path(out_path);
                    if (path.has_filename()) {
                        strcpy(buf.data(), path.filename().c_str());
                    }
                    NFD_FreePath(out_path);
                }
            }
        }
        ImGui::SeparatorText("Disabled");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr = R"(
                {
                    "label": "Input Disabled", 
                    "placeholder": "Email", 
                    "disabled": true
                }
            )"_json;
            Input(
                attr, 
                ImVec2(0, 0), 
                buf.data(), 
                buf.size()
            );
        }
        ImGui::SeparatorText("Invalid");
        {
            static std::vector<char> buf(1024);
            nlohmann::json attr = R"(
                {
                    "label": "Input Invalid", 
                    "type": "invalid", 
                    "placeholder": "Error"
                }
            )"_json;
            Input(
                attr, 
                ImVec2(0, 0), 
                buf.data(), 
                buf.size()
            );
        }
        ImGui::EndChild();
    }
}