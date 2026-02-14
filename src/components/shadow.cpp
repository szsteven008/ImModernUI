#include "shadow.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <vector>

namespace ImModernUI {
    struct ShadowLayerStyle {
        ImVec2 offset;
        float blur;
        float spread;
        ImVec4 col;
    };

    static void draw_shadow(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding, 
        std::vector<ShadowLayerStyle>& layers
    ) {
        for (const auto& layer : layers) {
            int steps = ImClamp(layer.blur, 1.0f, 8.0f);
            for (int i=0; i<steps; ++i) {
                float t = (i + 1) * 1.0f / steps;
                float spread = layer.spread + t * layer.blur;
                float alpha = layer.col.w * (1.0 - t);

                auto col = ImGui::GetColorU32(
                    {layer.col.x, layer.col.y, layer.col.z, alpha}
                );

                auto min = ImVec2(
                    bb.Min.x + layer.offset.x - spread, 
                    bb.Min.y + layer.offset.y - spread
                );
                auto max = ImVec2(
                    bb.Max.x + layer.offset.x + spread, 
                    bb.Max.y + layer.offset.y + spread
                );

                draw->AddRect(
                    min, 
                    max, 
                    col, 
                    rounding
                );
            }
        }
    }

    void shadow_xs(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    ) {
        std::vector<ShadowLayerStyle> layers {
            {
                    {0, 1.0}, 
                    2.0, 
                    0, 
                    {0, 0, 0, 0.05}
                }
        };

        draw_shadow(
            draw, 
            bb, 
            rounding, 
            layers
        );
    }

    void shadow_sm(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    ) {
        std::vector<ShadowLayerStyle> layers {
            {
                    {0, 1.0}, 
                    3.0, 
                    0, 
                    {0, 0, 0, 0.1}
                },
            {
                    {0, 1.0}, 
                    2.0, 
                    -1.0, 
                    {0, 0, 0, 0.1}
                },
        };

        draw_shadow(
            draw, 
            bb, 
            rounding, 
            layers
        );
    }

    void shadow_md(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    ) {
        std::vector<ShadowLayerStyle> layers {
            {
                    {0, 4.0}, 
                    6.0, 
                    -1.0, 
                    {0, 0, 0, 0.1}
                },
            {
                    {0, 2.0}, 
                    4.0, 
                    -2.0, 
                    {0, 0, 0, 0.1}
                },
        };

        draw_shadow(
            draw, 
            bb, 
            rounding, 
            layers
        );
    }
}