#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace ImModernUI {
    void shadow_xs(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    );

    void shadow_sm(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    );

    void shadow_md(
        ImDrawList* draw, 
        ImRect& bb, 
        float rounding
    );
}