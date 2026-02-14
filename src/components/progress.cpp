#include "progress.h"

#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "themes.h"

namespace ImModernUI {
    bool Progress(const std::string& label, int v) {
        float width = ImGui::GetContentRegionAvail().x;
        float height = UISizes::h_2();

        auto pos = ImGui::GetCursorScreenPos();

        ImRect bb {
            pos.x, pos.y, 
            pos.x + width, pos.y + height
        };
        ImGui::ItemSize(bb.GetSize());
        ImGui::ItemAdd(bb, ImGui::GetID(label.c_str()));

        auto draw = ImGui::GetWindowDrawList();
        const ImVec4 idle_col {
            UIThemes::primary().x, 
            UIThemes::primary().y, 
            UIThemes::primary().z, 
            0.2f
        };
        const ImVec4 filled_col = UIThemes::primary();
        if (v >= 100 || v <= 0) {
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32((v >= 100) ? filled_col : idle_col), 
                UISizes::rounded_full()
            );
        } else {
            float cur = v * width / 100.0f;
            draw->AddRectFilled(
                bb.Min, 
                ImVec2(
                    bb.Min.x + cur, 
                    bb.Max.y
                ), 
                ImGui::GetColorU32(filled_col), 
                UISizes::rounded_full(), 
                ImDrawFlags_RoundCornersLeft  
            );
            draw->AddRectFilled(
                ImVec2(
                    bb.Min.x + cur, 
                    bb.Min.y
                ), 
                bb.Max, 
                ImGui::GetColorU32(idle_col), 
                UISizes::rounded_full(), 
                ImDrawFlags_RoundCornersRight  
            );
        }

        return true;
    }

    void ShowProgressExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Progress Examples", 
            ImVec2(0, 0), flags);

        {
            static int v = 0;
            static float delta_time = 0.0f;
            static bool plus = true;

            delta_time += ImGui::GetIO().DeltaTime;
            if (delta_time >= 1.0) {
                v += (plus) ? 10 : -10;
                if (v <= 0) plus = true;
                if (v >= 100) plus = false;
                delta_time = 0.0f;
            }

            Progress("##Progress", v);
        }

        ImGui::EndChild();
    }
}