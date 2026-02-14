#pragma once

#include "global.h"
#include "imgui.h"
namespace ImModernUI {
    void BeginGroup(
        const ImVec2 spacing = ImVec2(
            UISizes::m_2(), 
            UISizes::m_2()
        )
    );
    void EndGroup();
}