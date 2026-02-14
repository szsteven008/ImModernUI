#include "avatar.h"

#include "global.h"
#include "image.h"
#include "imgui.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <string>
#include <vector>

namespace ImModernUI {
    struct AvatarStyle {
        static ImVec4 background() { return UIThemes::muted(); }
        static float size() { return UISizes::size_8(); }
        static float rounding(const std::string& r) {
            if (r == "xs") return UISizes::rounded_xs();
            if (r == "sm") return UISizes::rounded_sm();
            if (r == "md") return UISizes::rounded_md();
            if (r == "lg") return UISizes::rounded_lg();
            return UISizes::rounded_full();
        }
    };

    bool Avatar(const nlohmann::json& attr) {
        if (!attr.contains("label") || 
            !attr.contains("avatar")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string avatar = attr["avatar"].get<std::string>();
        std::string rounding = "full";
        if (attr.contains("rounding")) 
            rounding = attr["rounding"].get<std::string>();
        bool grayscale = false;
        if (attr.contains("grayscale")) 
            grayscale = attr["grayscale"].get<bool>();

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_ChildBg, AvatarStyle::background()}, 
        };
        for (const auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, ImGui::GetColorU32(col));
        }

        std::vector<std::tuple<ImGuiStyleVar, float>> style_vars_2 {
            {ImGuiStyleVar_ChildRounding, AvatarStyle::rounding(rounding)}, 
        };
        for (const auto& [idx, val]: style_vars_2) {
            ImGui::PushStyleVar(idx, val);
        }

        ImGui::BeginChild(
            label.c_str(), 
            ImVec2(AvatarStyle::size(), AvatarStyle::size())
        );

        int w, h;
        auto texture = ImModernUI::load_image(
            avatar.c_str(), &w, &h, grayscale
        );
        auto pos = ImGui::GetWindowPos();
        auto draw = ImGui::GetWindowDrawList();

        draw->AddRect(
            pos, 
            ImVec2(pos.x + AvatarStyle::size(), 
                pos.y + AvatarStyle::size()), 
            ImGui::GetColorU32(UIThemes::background()), 
            AvatarStyle::rounding(rounding)
        );

        draw->AddImageRounded(
            texture, 
            ImVec2(pos.x + 1.0, pos.y + 1.0), 
            ImVec2(pos.x + AvatarStyle::size() - 1.0, 
                pos.y + AvatarStyle::size() - 1.0), 
            ImVec2(0, 0), 
            ImVec2(1, 1), 
            IM_COL32_WHITE, 
            AvatarStyle::rounding(rounding)
        );

        ImGui::EndChild();

        ImGui::PopStyleVar(style_vars_2.size());
        ImGui::PopStyleColor(style_colors.size());

        return true;
    }

    void ShowAvatarExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Show Avatar Examples", 
            ImVec2(0, 0), flags);
        {
            nlohmann::json attr;
            attr["label"] = "shadcn";
            attr["avatar"] = "assets/images/124599.jpeg";
            attr["rounding"] = "full";
            Avatar(attr);
        }

        ImGui::SameLine();

        {
            nlohmann::json attr;
            attr["label"] = "evilrabbit";
            attr["avatar"] = "assets/images/6880091.png";
            attr["rounding"] = "lg";
            Avatar(attr);
        }

        ImGui::SameLine();

        {
            std::vector<const char *> images {
                "assets/images/124599.jpeg", 
                "assets/images/8675906.png", 
                "assets/images/6880091.png", 
            };

            ImGui::PushStyleVarX(ImGuiStyleVar_ItemSpacing, 
                -2 * UISizes::spacing());
            for (int i=0; i<images.size(); ++i) {
                if (i > 0) ImGui::SameLine();

                nlohmann::json attr;
                attr["label"] = "gray avatar." + std::to_string(i);
                attr["avatar"] = images[i];
                attr["rounding"] = "full";
                attr["grayscale"] = true;
                Avatar(attr);
            }
            ImGui::PopStyleVar();
        }

        ImGui::EndChild();
    }
}