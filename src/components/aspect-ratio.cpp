#include "aspect-ratio.h"

#include "global.h"
#include "image.h"
#include "imgui_internal.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <OpenGL/gltypes.h>

#include "imgui.h"
#include "themes.h"
#include <sstream>
#include <string>
#include <algorithm>

namespace ImModernUI {
    struct AspectRatioStyle {
        static ImVec4 background() { return UIThemes::muted(); };

        static float rounding(const std::string& r) {
            if (r == "xs") return UISizes::rounded_xs();
            if (r == "sm") return UISizes::rounded_sm();
            if (r == "md") return UISizes::rounded_md();
            if (r == "lg") return UISizes::rounded_lg();
            if (r == "xl") return UISizes::rounded_xl();
            if (r == "full") return UISizes::rounded_full();
            return UISizes::rounded_lg();
        }
    };

    bool AspectRatio(
        const nlohmann::json& attr, 
        float width /* = 0.0f */
    ) {
        if (!attr.contains("label") || 
            !attr.contains("ratio")) return false;

        auto parse_ration = [](const std::string& s) {
            int w, h;
            char slash;

            std::stringstream ss(s);
            ss >> w >> slash >> h;
            if (ss.fail()) return 1.0f;
            return float(w) / float(h);
        };

        std::string label = attr["label"].get<std::string>();
        std::string ratio_str = attr["ratio"].get<std::string>();
        std::string rounding = "lg";
        if (attr.contains("rounding")) {
            rounding = AspectRatioStyle::rounding(
                attr["rounding"].get<std::string>()
            );
        }
        std::string corner = "all";
        if (attr.contains("corner")) 
            corner = attr["corner"].get<std::string>();

        if (width == 0.0f) width = ImGui::GetContentRegionAvail().x;
        float ratio = parse_ration(ratio_str);
        float height = width / ratio;

        auto aspect_ratio_id = ImGui::GetID(label.c_str());
        ImGui::PushID(aspect_ratio_id);

        auto draw = ImGui::GetWindowDrawList();
        ImDrawFlags df = ImDrawFlags_RoundCornersAll;
        if (corner == "top")
            df = ImDrawFlags_RoundCornersTop;
        else if (corner == "bottom") 
            df = ImDrawFlags_RoundCornersBottom;
        else if (corner == "left")
            df = ImDrawFlags_RoundCornersLeft;
        else if (corner == "right")
            df = ImDrawFlags_RoundCornersRight;

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + width, 
            pos.y + height
        };
        ImGui::ItemSize(bb);
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(AspectRatioStyle::background()), 
            AspectRatioStyle::rounding(rounding), 
            df
        );

        GLuint texture;
        int w, h;
        if (attr.contains("image")) {
            std::string image = attr["image"].get<std::string>();
            texture = ImModernUI::load_image(image.c_str(), &w, &h);
        } else {
            texture = attr["texture"].get<GLuint>();
            w = attr["width"].get<int>();
            h = attr["height"].get<int>();
        }

        std::string fit = "cover";
        if (attr.contains("fit")) 
            fit = attr["fit"].get<std::string>();

        if (fit == "contain") {
            float scale = std::min(width / w, height / h);
            draw->AddImageRounded(
                texture, 
                ImVec2(
                    pos.x + width * 0.5 - scale * w * 0.5, 
                    pos.y + height * 0.5 - scale * h * 0.5
                ), 
                ImVec2(
                    pos.x + width * 0.5 + scale * w * 0.5, 
                    pos.y + height * 0.5 + scale * h * 0.5
                ), 
                ImVec2(0, 0), 
                ImVec2(1, 1), 
                IM_COL32_WHITE, 
                AspectRatioStyle::rounding(rounding), 
                df
            );
        } else if (fit == "cover") {
            float scale = std::max(width / w, height / h);
            draw->AddImageRounded(
                texture, 
                pos, 
                ImVec2(pos.x + width, pos.y + height), 
                ImVec2(0, 0), 
                ImVec2(width / w / scale, height / h / scale), 
                IM_COL32_WHITE, 
                AspectRatioStyle::rounding(rounding), 
                df
            );
        } else if (fit == "fill") {
            draw->AddImageRounded(
                texture, 
                pos, 
                ImVec2(pos.x + width, pos.y + height), 
                ImVec2(0, 0), 
                ImVec2(1, 1), 
                IM_COL32_WHITE, 
                AspectRatioStyle::rounding(rounding), 
                df
            );
        }

        ImGui::PopID();

        return true;
    }

    void ShowAspectRatioExamples() {
        ImGui::SeparatorText("Contain");
        {
            nlohmann::json attr;
            attr["label"] = "##Aspect Ratio Examples: Contain";
            attr["ratio"] = "16/9";
            attr["rounding"] = "lg";
            attr["image"] = "assets/images/photo-1554629947-334ff61d85dc.jpg";
            attr["fit"] = "contain";
            ImModernUI::AspectRatio(attr);
        }
        ImGui::SeparatorText("Cover");
        {
            nlohmann::json attr;
            attr["label"] = "##Aspect Ratio Examples: Cover";
            attr["ratio"] = "16/9";
            attr["rounding"] = "lg";
            attr["image"] = "assets/images/photo-1554629947-334ff61d85dc.jpg";
            attr["fit"] = "cover";
            ImModernUI::AspectRatio(attr);
        }
        ImGui::SeparatorText("Fill");
        {
            nlohmann::json attr;
            attr["label"] = "##Aspect Ratio Examples: Fill";
            attr["ratio"] = "16/9";
            attr["rounding"] = "lg";
            attr["image"] = "assets/images/photo-1554629947-334ff61d85dc.jpg";
            attr["fit"] = "fill";
            ImModernUI::AspectRatio(attr);
        }
    }
}