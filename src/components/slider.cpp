#include "slider.h"

#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "themes.h"
#include <algorithm>
#include <string>

namespace ImModernUI {
    static bool horizontal_slider(
        const std::string& label,
        int min, 
        int max, 
        int step, 
        int * v
    ) {
        auto label_size_h = ImGui::CalcTextSize(label.c_str()).y;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, 
            ImVec2(0, (UISizes::size_4() - label_size_h) * 0.5));

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        bool changed = ImGui::SliderInt(
            label.c_str(), 
            v, 
            min, 
            max
        );

        ImRect bb {
            ImGui::GetItemRectMin(), 
            ImGui::GetItemRectMax()
        };

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(UIThemes::background())
        );

        float radius = UISizes::size_4() * 0.5;
        ImVec2 track_base_line {
            bb.Min.x + radius, 
            (bb.Min.y + bb.Max.y) * 0.5f
        };
        float track_width = bb.GetWidth() - UISizes::size_4();
        float track_height = 1.5f * UISizes::spacing();
        float cur_track_width = *v * 1.0f / (max - min) * track_width;
        float cur_track_x = track_base_line.x + cur_track_width;

        ImRect filled_bb {
            track_base_line.x, 
            track_base_line.y - track_height * 0.5f, 
            cur_track_x, 
            track_base_line.y + track_height * 0.5f
        };
        draw->AddRectFilled(
            filled_bb.Min, 
            filled_bb.Max, 
            ImGui::GetColorU32(UIThemes::primary()), 
            UISizes::rounded_full()
        );

        ImRect idle_bb {
            cur_track_x, 
            track_base_line.y - track_height * 0.5f, 
            track_base_line.x + track_width, 
            track_base_line.y + track_height * 0.5f
        };
        draw->AddRectFilled(
            idle_bb.Min, 
            idle_bb.Max, 
            ImGui::GetColorU32(UIThemes::muted()), 
            UISizes::rounded_full()
        );

        ImRect grab_bb {
            cur_track_x - radius, 
            bb.Min.y, 
            cur_track_x + radius, 
            bb.Max.y
        };
        draw->AddCircleFilled(
            ImVec2(
                cur_track_x, 
                track_base_line.y
            ), 
            radius, 
            ImGui::GetColorU32(UIColors::color_white), 
            128
        );
        draw->AddCircle(
            ImVec2(
                cur_track_x, 
                track_base_line.y
            ), 
            radius, 
            ImGui::GetColorU32(UIThemes::primary()), 
            128
        );

        auto mouse = ImGui::GetMousePos();
        if (grab_bb.Contains(mouse) || ImGui::IsItemActive()) {
            draw->AddCircle(
                ImVec2(
                    track_base_line.x + cur_track_width, 
                    track_base_line.y
                ), 
                radius + 2.0f, 
                ImGui::GetColorU32(UIThemes::ring()), 
                128, 
                3.0f
            );
        }

        ImGui::PopStyleVar();

        return changed;
    }

    static bool vertical_slider(
        const std::string& label,
        int min, 
        int max, 
        int step, 
        int * v
    ) {
        auto height = ImGui::GetContentRegionAvail().y;
        height = std::max(height, UISizes::h_44());
        auto width = UISizes::size_4();
        bool changed = ImGui::VSliderInt(
            label.c_str(), 
            ImVec2(width, height), 
            v, 
            min, 
            max
        );

        ImRect bb {
            ImGui::GetItemRectMin(), 
            ImGui::GetItemRectMax()
        };

        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(
            bb.Min, 
            bb.Max, 
            ImGui::GetColorU32(UIThemes::background())
        );

        float radius = UISizes::size_4() * 0.5;
        ImVec2 track_base_line {
            bb.Min.x + radius, 
            bb.Min.y + radius
        };
        float track_width = 1.5f * UISizes::spacing();
        float track_height = bb.GetHeight() - UISizes::size_4();
        float cur_track_height = *v * 1.0f / (max - min) * track_height;
        float cur_track_y = track_base_line.y + track_height - cur_track_height;

        ImRect idle_bb {
            track_base_line.x - track_width * 0.5f, 
            track_base_line.y, 
            track_base_line.x + track_width * 0.5f, 
            cur_track_y
        };
        draw->AddRectFilled(
            idle_bb.Min, 
            idle_bb.Max, 
            ImGui::GetColorU32(UIThemes::muted()), 
            UISizes::rounded_full()
        );

        ImRect filled_bb {
            track_base_line.x - track_width * 0.5f, 
            cur_track_y, 
            track_base_line.x + track_width * 0.5f, 
            track_base_line.y + track_height
        };
        draw->AddRectFilled(
            filled_bb.Min, 
            filled_bb.Max, 
            ImGui::GetColorU32(UIThemes::primary()), 
            UISizes::rounded_full()
        );

        ImRect grab_bb {
            bb.Min.x, 
            cur_track_y - radius, 
            bb.Max.x, 
            cur_track_y + radius, 
        };
        draw->AddCircleFilled(
            ImVec2(
                track_base_line.x, 
                cur_track_y
            ), 
            radius, 
            ImGui::GetColorU32(UIColors::color_white), 
            128
        );
        draw->AddCircle(
            ImVec2(
                track_base_line.x, 
                cur_track_y
            ), 
            radius, 
            ImGui::GetColorU32(UIThemes::primary()), 
            128
        );

        auto mouse = ImGui::GetMousePos();
        if (grab_bb.Contains(mouse) || ImGui::IsItemActive()) {
            draw->AddCircle(
                ImVec2(
                    track_base_line.x, 
                    track_base_line.y + track_height - cur_track_height
                ), 
                radius + 2.0f, 
                ImGui::GetColorU32(UIThemes::ring()), 
                128, 
                3.0f
            );
        }

        return changed;
    }

    bool Slider(const nlohmann::json& attr, int * v) {
        if (!attr.contains("label")) return false;
        std::string label = attr["label"].get<std::string>();
        std::string orientation = "horizontal";
        if (attr.contains("orientation")) 
            orientation = attr["orientation"].get<std::string>();
        int min = 0;
        if (attr.contains("min")) 
            min = attr["min"].get<int>();
        int max = 100;
        if (attr.contains("max")) 
            max = attr["max"].get<int>();
        int step = 1;
        if (attr.contains("step")) 
            step = attr["step"].get<int>();

        if (orientation == "vertical") {
            vertical_slider(
                label, 
                min, 
                max, 
                step, 
                v
            );
        } else {
            horizontal_slider(
                label, 
                min, 
                max, 
                step, 
                v
            );
        }

        return true;
    }

    void ShowSliderExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        ImGui::BeginChild("##Slider Examples", 
            ImVec2(0, 0), flags);

        ImGui::SeparatorText("Horizontal");
        {
            static int v = 50;
            nlohmann::json attr;
            attr["label"] = "##Horizontal Slider Example";
            attr["min"] = 0;
            attr["max"] = 100;
            attr["step"] = 1;
            Slider(attr, &v);
        }

        ImGui::SeparatorText("Vertical");
        {
            static int v = 50;
            nlohmann::json attr;
            attr["label"] = "##Vertical Slider Example";
            attr["orientation"] = "vertical";
            attr["min"] = 0;
            attr["max"] = 100;
            attr["step"] = 1;
            Slider(attr, &v);
        }

        ImGui::EndChild();
    }
}