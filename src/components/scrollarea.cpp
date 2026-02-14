#include "scrollarea.h"
#include "aspect-ratio.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "label.h"
#include "nlohmann/json_fwd.hpp"
#include "separator.h"
#include "state.h"
#include "themes.h"
#include "nlohmann/json.hpp"
#include <format>
#include <tuple>
#include <vector>

namespace ImModernUI {
    bool BeginScrollArea(
        const std::string& label,
        const ImVec2& size_arg, 
        const std::string orientation /* = "vertical" */
    ) {
        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        nlohmann::json state;
        state["id"] = id;
        UIState::PushState(state);

        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, 
            UIColors::color_transparent);

        bool hovered = ImGui::GetStateStorage()->GetBool(id);
        if (hovered) {
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, 
                UIThemes::border());
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, 
                UIThemes::border());
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, 
                UIThemes::border());
        } else {
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, 
                UIColors::color_transparent);
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, 
                UIColors::color_transparent);
            ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, 
                UIColors::color_transparent);
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
            ImVec2(UISizes::p_4(), UISizes::p_4()));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
            ImVec2(UISizes::m_4(), UISizes::m_4()));

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 
            UISizes::rounded_md());
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 
            2.5f * UISizes::spacing());
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 
            UISizes::rounded_full());

        ImGuiChildFlags flags = ImGuiChildFlags_Borders;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;

        if (size_arg.x == 0.0f) flags |= ImGuiChildFlags_AutoResizeX;
        if (size_arg.y == 0.0f) flags |= ImGuiChildFlags_AutoResizeY;

        ImGuiWindowFlags window_flags = ((orientation == "vertical") ? 
            ImGuiWindowFlags_AlwaysVerticalScrollbar : 
            ImGuiWindowFlags_AlwaysHorizontalScrollbar
        );

        bool ret = ImGui::BeginChild(
            id, 
            size_arg, 
            flags, 
            window_flags
        );

        return ret;
    }

    void EndScrollArea() {
        auto mouse_pos = ImGui::GetMousePos();
        auto pos = ImGui::GetWindowPos();
        auto size = ImGui::GetWindowSize();
        ImRect bb {
            pos.x, pos.y, 
            pos.x + size.x, pos.y + size.y
        };

        ImGui::EndChild();
        ImGui::PopStyleVar(5);
        ImGui::PopStyleColor(4);

        auto& state = UIState::PeekState();
        auto id = state["id"].get<unsigned int>();
        ImGui::GetStateStorage()->SetBool(id, bb.Contains(mouse_pos));
        UIState::PopState();

        ImGui::PopID();
    }

    void ShowScrollAreaExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Scrollarea Examples Window", 
            ImVec2(0, 0), flags);
        ImGui::SeparatorText("Vertical");
        {
            BeginScrollArea(
                "##Scrollarea Vertical", 
                ImVec2(UISizes::w_48(), UISizes::h_72())
            );

            ImModernUI::Label("Tags", false);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
                ImVec2(UISizes::m_2(), UISizes::m_2()));
            ImGui::PushFont(UIFont::font_regular_sm());
            for (int i=50; i>0; --i) {
                ImGui::TextUnformatted(
                    std::format("v1.2.0-beta.{}", i).c_str()
                );
                ImModernUI::Separator();
            }
            ImGui::PopFont();
            ImGui::PopStyleVar();

            EndScrollArea();
        }
        ImGui::SeparatorText("Horizontal");
        {
            BeginScrollArea(
                "##Scrollarea Horizontal", 
                ImVec2(UISizes::w_96(), 0), 
                "horizontal"
            );

            std::vector<std::tuple<std::string, std::string>> photos {
                {
                        "Ornella Binni", 
                        "assets/images/photo-1465869185982-5a1a7522cbcb.png"
                    }, 
                {
                        "Tom Byrom", 
                        "assets/images/photo-1548516173-3cabfa4607e9.png"
                    }, 
                {
                        "Vladimir Malyavko", 
                        "assets/images/photo-1494337480532-3725c85fd2ab.png"
                    }, 
            };

            for (auto& photo: photos) {
                if (photo != photos.front()) ImGui::SameLine();

                std::string artist, art;
                tie(artist, art) = photo;

                ImGui::BeginGroup();
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
                        ImVec2(UISizes::m_2(), UISizes::m_2()));
                    ImGui::BeginChild(
                        std::format("##image {}", artist).c_str(), 
                        ImVec2(150, 200)
                    );

                    nlohmann::json attr;
                    attr["label"] = "##" + artist;
                    attr["ratio"] = "3/4";
                    attr["rounding"] = "md";
                    attr["image"] = art;
                    attr["fit"] = "cover";
                    ImModernUI::AspectRatio(attr);

                    ImGui::EndChild();

                    {
                        ImGui::BeginGroup();
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
                            ImVec2(0, 0));

                        ImGui::PushStyleColor(ImGuiCol_Text, 
                            UIThemes::muted_foreground());
                        ImGui::PushFont(UIFont::font_regular_xs());
                        ImGui::TextUnformatted("Photo by ");
                        ImGui::PopFont();
                        ImGui::PopStyleColor();
                        ImGui::SameLine();
                        ImGui::PushFont(UIFont::font_semibold_xs());
                        ImGui::TextUnformatted(artist.c_str());
                        ImGui::PopFont();

                        ImGui::PopStyleVar();
                        ImGui::EndGroup();
                    }

                    ImGui::PopStyleVar();
                }
                ImGui::EndGroup();
            }

            EndScrollArea();
        }
        ImGui::EndChild();
    }

}