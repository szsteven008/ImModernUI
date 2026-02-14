#include "input-group.h"
#include "button.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "input.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include "toggle.h"
#include <vector>
#include <iostream>

namespace ImModernUI {
    static bool inputgroup_inline(
        const std::string& placeholder, 
        char * buf, 
        int buf_size, 
        bool readonly, 
        std::function<void(float, char *, int)> prefix, 
        std::function<void(float, char *, int)> suffix
    ) {
        auto min = ImGui::GetItemRectMin();
        auto size = ImGui::GetItemRectSize();

        float offset = UISizes::p_2();
        ImGui::SetCursorScreenPos(
            ImVec2(
                min.x + offset, 
                min.y
            )
        );
        bool changed = false;
        float width = size.x - 2 * offset;
        if (prefix) {
            ImGui::BeginGroup();
            prefix(size.y, buf, buf_size);
            ImGui::EndGroup();
            float x = ImGui::GetItemRectSize().x;
            width -= x;
            offset += x;

            width -= UISizes::m_2();
            offset += UISizes::m_2();
        }

        if (suffix) {
            ImGui::SetCursorScreenPos(
                ImVec2(
                    min.x + offset, 
                    min.y
                )
            );

            ImGui::PushID(ImGui::GetID("##Input Group Suffix.disabled"));
            ImGui::BeginDisabled();
            ImGui::BeginGroup();
            suffix(size.y, buf, buf_size);
            ImGui::EndGroup();
            ImGui::EndDisabled();
            ImGui::PopID();

            auto draw = ImGui::GetWindowDrawList();
            auto suffix_min = ImGui::GetItemRectMin();
            auto suffix_max = ImGui::GetItemRectMax();
            draw->AddRectFilled(
                ImVec2(suffix_min.x, suffix_min.y + 1.0), 
                ImVec2(suffix_max.x, suffix_max.y - 1.0), 
                ImGui::GetColorU32(UIThemes::background())
            );

            width -= ImGui::GetItemRectSize().x;
            width -= UISizes::m_2();
        }

        ImGui::SetCursorScreenPos(
            ImVec2(
                min.x + offset, 
                min.y
            )
        );

        nlohmann::json attr;
        attr["label"] = "##input";
        attr["placeholder"] = placeholder;
        attr["border"] = false;
        attr["disabled"] = readonly;
        changed = Input(
            attr, 
            ImVec2(width, size.y), 
            buf, 
            buf_size
        );
        offset += width;
        offset += UISizes::m_2();

        if (suffix) {
            ImGui::SetCursorScreenPos(
                ImVec2(
                    min.x + offset, 
                    min.y
                )
            );
            ImGui::BeginGroup();
            suffix(size.y, buf, buf_size);
            ImGui::EndGroup();
        }

        return changed;
    }

    bool InputGroup(
        const std::string& label, 
        const std::string& placeholder, 
        char * buf, 
        int buf_size, 
        bool border /* = true */, 
        bool readonly /* = false */, 
        ImVec2 size_arg /* = ImVec2(0, 0) */, 
        const std::string align /* = "inline" */, // inline|block
        std::function<void(float, char *, int)> prefix /* = nullptr */, 
        std::function<void(float, char *, int)> suffix /* = nullptr */
    ) {
        if (size_arg.x == 0) 
            size_arg.x = ImGui::GetContentRegionAvail().x;
        if (size_arg.y == 0) {
            size_arg.y = UISizes::h_9();
            if (align == "block") 
                size_arg.y = ImGui::GetContentRegionAvail().y;
        }

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        ImGui::BeginGroup();
        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + size_arg.x, 
            pos.y + size_arg.y
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, id);

        if (border) {
            auto draw = ImGui::GetWindowDrawList();
            draw->AddRect(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(UIThemes::input()), 
                UISizes::rounded_md()
            );
        }

        bool changed = false;
        if (align == "block") {

        } else {
            changed = inputgroup_inline(
                placeholder, 
                buf, 
                buf_size, 
                readonly, 
                prefix, 
                suffix
            );
        }
        ImGui::EndGroup();

        ImGui::PopID();

        return changed;
    }

    void ShowInputGroupExamples() {
        ImGui::SeparatorText("Icon");
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Icon#1", 
                "Search...", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_icon());
                    ImGui::TextUnformatted(ICON_SEARCH);
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Icon#2", 
                "Enter your email", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_icon());
                    ImGui::TextUnformatted(ICON_MAIL);
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Icon#3", 
                "Card number", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_icon());
                    ImGui::TextUnformatted(ICON_CREDIT_CARD);
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_icon());
                    ImGui::TextUnformatted(ICON_CHECK);
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Icon#4", 
                "Card number", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                nullptr, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_icon());
                    ImGui::TextUnformatted(ICON_STAR);
                    ImGui::SameLine();
                    ImGui::TextUnformatted(ICON_INFO);
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        ImGui::SeparatorText("Text");
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Text#1", 
                "0.00", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_medium_base());
                    ImGui::TextUnformatted("$");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_medium_base());
                    ImGui::TextUnformatted("USD");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Text#2", 
                "example.com", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_medium_base());
                    ImGui::TextUnformatted("https://");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_medium_base());
                    ImGui::TextUnformatted(".com");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Text#3", 
                "Enter your username", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                nullptr, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::text_base()) * 0.5
                        )
                    );
                    ImGui::PushStyleColor(ImGuiCol_Text, 
                        UIThemes::muted_foreground());
                    ImGui::PushFont(UIFont::font_medium_base());
                    ImGui::TextUnformatted("@company.com");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
            );
        }
        ImGui::SeparatorText("Button");
        {
            static std::vector<char> buf(1024);
            static bool copied = false;
            InputGroup(
                "##InputGroup: Button#1", 
                "https://x.com/shadcn", 
                buf.data(), 
                buf.size(), 
                true, 
                true, 
                ImVec2(0, 0), 
                "inline", 
                nullptr, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();

                    nlohmann::json attr = R"(
                        {
                            "label": "##Copy",
                            "variant": "ghost",
                            "size": "icon-xs"
                        }
                    )"_json;
                    attr["icon"] = (copied ? ICON_CHECK : ICON_COPY);

                    auto size = ImModernUI::CalcButtonSize(attr);

                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - size.y) * 0.5
                        )
                    );

                    if (ImModernUI::Button(attr)) copied = true;
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Button#2", 
                "", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                nullptr, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();

                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - UISizes::h_6()) * 0.5
                        )
                    );

                    nlohmann::json attr;
                    attr["label"] = "##Toggle Star";
                    attr["icon"] = "assets/icons/star.svg";
                    attr["variant"] = "ghost";
                    attr["size"] = "xs";
                    static bool on = false;

                    ImModernUI::Toggle(attr, &on);
                }
            );
        }
        {
            static std::vector<char> buf(1024);
            InputGroup(
                "##InputGroup: Button#3", 
                "Type to search...", 
                buf.data(), 
                buf.size(), 
                true, 
                false, 
                ImVec2(0, 0), 
                "inline", 
                nullptr, 
                [](
                    float height, 
                    char * buf, 
                    int buf_size
                ) {
                    auto pos = ImGui::GetCursorScreenPos();

                    nlohmann::json attr = R"(
                        {
                            "label": "Search",
                            "variant": "secondary",
                            "size": "xs"
                        }
                    )"_json;

                    auto size = ImModernUI::CalcButtonSize(attr);

                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            pos.x, 
                            pos.y + (height - size.y) * 0.5
                        )
                    );

                    if (ImModernUI::Button(attr)) 
                        std::cout << "Search clicked!" << std::endl;
                }
            );
        }
        ImGui::SeparatorText("Dropdown");
        ImGui::SeparatorText("Spinner");
        ImGui::SeparatorText("Textarea");
        ImGui::SeparatorText("Custom Input");
    }
}