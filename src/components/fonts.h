#pragma once

#include "imgui.h"

namespace ImModernUI {
    struct UIFont {
        static bool load_fonts();

        static ImFont * font_regular_base();
        static ImFont * font_regular_xs();
        static ImFont * font_regular_sm();
        static ImFont * font_regular_lg();

        static ImFont * font_medium_base();
        static ImFont * font_medium_xs();
        static ImFont * font_medium_sm();
        static ImFont * font_medium_lg();

        static ImFont * font_semibold_base();
        static ImFont * font_semibold_xs();
        static ImFont * font_semibold_sm();
        static ImFont * font_semibold_lg();

        static ImFont * font_bold_base();
        static ImFont * font_bold_xs();
        static ImFont * font_bold_sm();
        static ImFont * font_bold_lg();

        static ImFont * font_icon();
        static ImFont * font_icon_sm();
    };
}