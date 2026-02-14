#include "card.h"

#include "aspect-ratio.h"
#include "badge.h"
#include "button.h"
#include "fonts.h"
#include "global.h"
#include "group.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "input.h"
#include "label.h"
#include "link.h"
#include "nlohmann/json_fwd.hpp"
#include "shadow.h"
#include "themes.h"
#include "nlohmann/json.hpp"
#include <algorithm>
#include <cfloat>
#include <cstring>
#include <format>
#include <string>
#include <iostream>
#include <vector>

namespace ImModernUI {
    struct CardStyle {
        static ImVec4 background() { return UIThemes::card(); }
        static ImVec4 foreground() { return UIThemes::card_foreground(); }
        static ImVec4 border() { return UIThemes::border(); }

        static ImVec2 padding() { 
            return ImVec2(UISizes::p_6(), 0); 
        }
        static ImVec2 gap() { 
            return ImVec2(UISizes::m_6(), UISizes::m_6()); 
        }

        static float rounding() { return UISizes::rounded_xl(); }
    };

    static bool card_header(
        const std::string& image, 
        const std::string& title, 
        const std::string& description, 
        const nlohmann::json& data, 
        std::function<void(const nlohmann::json&)> action
    ) {
        if (image.empty()) {
            ImGui::Dummy(ImVec2(0, 0));
        } else {
            float width = ImGui::GetWindowWidth();

            ImGui::SetCursorPosX(0);
            nlohmann::json attr;
            attr["label"] = "##card image";
            attr["ratio"] = "16/9";
            attr["rounding"] = "xl";
            attr["image"] = image.c_str();
            attr["fit"] = "cover";
            attr["corner"] = "top";
            ImModernUI::AspectRatio(attr, width);
        }
        float max_width = ImGui::GetContentRegionAvail().x;
        auto pos = ImGui::GetCursorPos();
        if (action) {
            ImGui::PushID("##card header action clone");
            ImGui::BeginDisabled();
            action(data);
            ImGui::EndDisabled();
            ImGui::PopID();
            auto min = ImGui::GetItemRectMin();
            auto max = ImGui::GetItemRectMax();

            auto draw = ImGui::GetWindowDrawList();
            draw->AddRectFilled(
                min, 
                max, 
                ImGui::GetColorU32(CardStyle::background())
            );

            max_width -= (max.x - min.x);
            ImGui::SetCursorPos(
                ImVec2(pos.x + max_width, pos.y)
            );
            action(data);
            max_width -= CardStyle::gap().x;
            ImGui::SetCursorPos(pos);
        }

        if (!title.empty()) {
            ImModernUI::BeginGroup();
            ImGui::PushFont(UIFont::font_semibold_base());
            ImGui::TextUnformatted(title.c_str());
            ImGui::PopFont();
            if (!description.empty()) {
                ImGui::PushFont(UIFont::font_regular_sm());
                ImGui::PushStyleColor(ImGuiCol_Text, 
                    UIThemes::muted_foreground());
                ImGui::PushTextWrapPos(
                    ImGui::GetCursorPosX() + max_width
                );
                ImGui::TextUnformatted(description.c_str());
                ImGui::PopTextWrapPos();
                ImGui::PopStyleColor();
                ImGui::PopFont();
            }
            ImModernUI::EndGroup();
        }

        return true;
    }

    static bool card_content(
        nlohmann::json& data, 
        std::function<void(nlohmann::json&)> content
    ) {
        ImGui::BeginGroup();
        content(data);
        ImGui::EndGroup();

        return true;        
    }

    static bool card_footer(
        nlohmann::json& data, 
        std::function<void(nlohmann::json&)> footer
    ) {
        ImDrawListSplitter dls;
        auto dl = ImGui::GetWindowDrawList();
        dls.Split(dl, 2);

        dls.SetCurrentChannel(dl, 1);
        ImModernUI::BeginGroup();
        ImGui::Dummy(ImVec2(0, UISizes::p_3()));
        footer(data);
        ImGui::Dummy(ImVec2(0, UISizes::p_3()));
        ImModernUI::EndGroup();

        dls.SetCurrentChannel(dl, 0);
        auto& style = ImGui::GetStyle();
        auto min = ImGui::GetItemRectMin();
        auto max = ImGui::GetItemRectMax();

        min = ImVec2(
            min.x - style.WindowPadding.x, 
            min.y
        );
        max = ImVec2(
            max.x + style.WindowPadding.x, 
            max.y + style.WindowPadding.y
        );
        dl->AddRectFilled(
            min, 
            max, 
            ImGui::GetColorU32(UIThemes::muted()), 
            UISizes::rounded_xl(), 
            ImDrawFlags_RoundCornersBottom
        );
        dl->AddRect(
            min, 
            max, 
            ImGui::GetColorU32(CardStyle::border()), 
            UISizes::rounded_xl(), 
            ImDrawFlags_RoundCornersBottom
        );
        dls.Merge(dl);

        return true;
    }

    bool Card(
        const nlohmann::json& attr, 
        const ImVec2& size_arg, 
        nlohmann::json& data, 
        std::function<void(const nlohmann::json&)> action /* = nullptr */, 
        std::function<void(nlohmann::json&)> content /* = nullptr */, 
        std::function<void(const nlohmann::json&)> footer /* = nullptr */
    ) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string image = "";
        if (attr.contains("image")) 
            image = attr["image"].get<std::string>();
        std::string title = ""; 
        if (attr.contains("title"))
            title = attr["title"].get<std::string>();
        std::string description = "";
        if (attr.contains("description")) 
            description = attr["description"].get<std::string>();

        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_ChildBg, CardStyle::background()}, 
            {ImGuiCol_Text, CardStyle::foreground()}, 
            {ImGuiCol_Border, CardStyle::border()},
        };
        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, CardStyle::padding()},
            {ImGuiStyleVar_ItemSpacing, CardStyle::gap()}, 
        };
        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_ChildRounding, CardStyle::rounding()}, 
            {ImGuiStyleVar_ChildBorderSize, 1.0f}, 
        };

        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }
        for (const auto& [idx, var]: style_vars_2) {
            ImGui::PushStyleVar(idx, var);
        }

        float x = (size_arg.x == 0) ? 
            ImGui::GetContentRegionAvail().x : size_arg.x;
        float y = size_arg.y;

        ImGuiChildFlags flags = ImGuiChildFlags_AlwaysUseWindowPadding;
        if (y == 0) flags |= ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_Borders;

        if (ImGui::BeginChild(
            id, 
            ImVec2(x, y), 
            flags, 
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
        )) {
            card_header(
                image, 
                title, 
                description, 
                data, 
                action
            );

            if (content) card_content(data, content);                

            if (footer) {
                card_footer(data, footer);
            } else {
                ImGui::Dummy(ImVec2(0, 0));
            }
        }

        ImGui::EndChild();

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());

        auto draw = ImGui::GetWindowDrawList();
        auto min = ImGui::GetItemRectMin();
        auto max = ImGui::GetItemRectMax();
        ImRect bb {
            min.x, 
            min.y, 
            max.x, 
            max.y
        };

        shadow_xs(
            draw, 
            bb, 
            CardStyle::rounding() + 3.0
        );

        ImGui::PopID();

        return true;
    }

    void ShowCardExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Card Examples Child Window", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Base");
        {
            nlohmann::json attr;
            attr["label"] = "##Card Examples";
            attr["title"] = "Login to your account";
            attr["description"] = "Enter your email below to login to your account";

            static nlohmann::json data;
            Card(
                attr, 
                ImVec2(UISizes::basis_sm(), 0), 
                data, 
                [](const nlohmann::json& data) {
                    nlohmann::json attr;
                    attr["label"] = "Sign Up";
                    attr["variant"] = "link";
                    if (ImModernUI::Button(attr)) {
                        std::cout << "Sign Up Clicked!" << std::endl;
                    }
                }, 
                [](nlohmann::json& data) {
                    {
                        ImModernUI::BeginGroup();
                        Label("Email", false);
                        std::vector<char> buf(1024, 0x0);
                        if (data.contains("email")) {
                            std::string s = data["email"].get<std::string>();
                            int n = std::min(buf.size() -1, s.size());
                            std::memcpy(buf.data(), s.data(), n);
                        }

                        nlohmann::json attr;
                        attr["label"] = "Email";
                        attr["placeholder"] = "m@example.com";
                        if (ImModernUI::Input(
                            attr, 
                            ImVec2(0, 0), 
                            buf.data(), 
                            buf.size()
                        )) data["email"] = std::string(buf.data());
                        ImModernUI::EndGroup();
                    }

                    {
                        ImModernUI::BeginGroup();
                        Label("Password", false);
                        ImGui::SameLine();
                        ImGui::PushFont(UIFont::font_regular_sm());
                        std::string a = "Forgot your password?";
                        auto x = ImGui::GetContentRegionAvail().x;
                        x -= ImGui::CalcTextSize(a.c_str()).x;
                        ImGui::SetCursorPosX(
                            ImGui::GetCursorPosX() + x
                        );
                        if (ImModernUI::link(a)) {
                            std::cout << std::format("{} - clicked!\n", a);
                        }
                        ImGui::PopFont();

                        static std::vector<char> buf(1024, 0x0);
                        if (data.contains("password")) {
                            std::string s = data["password"].get<std::string>();
                            int n = std::min(buf.size() -1, s.size());
                            std::memcpy(buf.data(), s.data(), n);
                        }
                        nlohmann::json attr;
                        attr["label"] = "##Password";
                        attr["type"] = "password";
                        if (ImModernUI::Input(
                            attr, 
                            ImVec2(0, 0), 
                            buf.data(), 
                            buf.size()
                        )) data["password"] = std::string(buf.data());
                        ImModernUI::EndGroup();
                    }

                }, 
                [](const nlohmann::json& data) {
                    nlohmann::json attr;
                    attr["label"] = "Login";
                    attr["size"] = "full";
                    if (ImModernUI::Button(attr)) {
                        std::cout << "Login action!" << std::endl;
                        std::cout << data.dump() << std::endl;
                    }

                    attr["label"] = "Login with Google";
                    attr["variant"] = "outline";
                    attr["size"] = "full";
                    if (ImModernUI::Button(attr)) {
                        std::cout << "Login with Google action!" << std::endl;
                        std::cout << data.dump() << std::endl;
                    }
                }
            );
        }

        ImGui::SeparatorText("Size");
        {
            nlohmann::json attr;
            attr["label"] = "##Card Examples: Size";
            attr["title"] = "Small Card";
            attr["description"] = "This card uses the small size variant.";

            nlohmann::json data = nlohmann::json::value_t::null;
            Card(
                attr, 
                ImVec2(UISizes::basis_sm(), 0), 
                data, 
                nullptr, 
                [](nlohmann::json& data) {
                    float x = ImGui::GetContentRegionAvail().x;
                    ImGui::PushTextWrapPos(
                        ImGui::GetCursorPosX() + x
                    );
                    ImGui::TextUnformatted("The card component supports a size prop "
                        "that can be set to \"sm\" for a more compact appearance.");
                    ImGui::PopTextWrapPos();
                }, 
                [](const nlohmann::json& data) {
                    nlohmann::json attr;
                    attr["label"] = "Action";
                    attr["variant"] = "outline";
                    attr["size"] = "full-sm";
                    if (ImModernUI::Button(attr)) {
                        std::cout << "Action click!" << std::endl;
                    }
                }
            );
        }

        ImGui::SeparatorText("Image");
        {
            nlohmann::json attr;
            attr["label"] = "##Card Examples: Image";
            attr["image"] = "assets/images/photo-1554629947-334ff61d85dc.jpg";
            attr["title"] = "Design systems meetup";
            attr["description"] = "A practical talk on component APIs, "
                "accessibility, and shipping faster.";

            nlohmann::json data = nlohmann::json::value_t::null;
            Card(
                attr, 
                ImVec2(UISizes::basis_sm(), 0), 
                data, 
                [](const nlohmann::json& data) {
                    nlohmann::json attr;
                    attr["label"] = "Featured";
                    attr["variant"] = "secondary";
                    ImModernUI::Badge(attr);
                }, 
                nullptr, 
                [](const nlohmann::json& data) {
                    nlohmann::json attr;
                    attr["label"] = "View Event";
                    attr["variant"] = "primary";
                    attr["size"] = "full-sm";
                    if (ImModernUI::Button(attr)) {
                        std::cout << "View Event Click!" << std::endl;
                    }
                }
            );
        }

        ImGui::EndChild();
    }
}