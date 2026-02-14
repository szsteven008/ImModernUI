#include "fonts.h"
#include "global.h"
#include "imgui.h"

namespace ImModernUI {
    static ImFont * ui_font_regular_base = nullptr;
    static ImFont * ui_font_regular_xs = nullptr;
    static ImFont * ui_font_regular_sm = nullptr;
    static ImFont * ui_font_regular_lg = nullptr;

    static ImFont * ui_font_medium_base = nullptr;
    static ImFont * ui_font_medium_xs = nullptr;
    static ImFont * ui_font_medium_sm = nullptr;
    static ImFont * ui_font_medium_lg = nullptr;

    static ImFont * ui_font_semibold_base = nullptr;
    static ImFont * ui_font_semibold_xs = nullptr;
    static ImFont * ui_font_semibold_sm = nullptr;
    static ImFont * ui_font_semibold_lg = nullptr;

    static ImFont * ui_font_bold_base = nullptr;
    static ImFont * ui_font_bold_xs = nullptr;
    static ImFont * ui_font_bold_sm = nullptr;
    static ImFont * ui_font_bold_lg = nullptr;

    static ImFont * ui_font_icon = nullptr;
    static ImFont * ui_font_icon_sm = nullptr;

    bool UIFont::load_fonts() {
        ImGui::GetIO().Fonts->AddFontDefault();

        auto load_font = 
            [](const char * name, float size, bool merge) {
            ImFontConfig fc;
            fc.MergeMode = merge;
            if (merge) {
                fc.PixelSnapH = true;
                fc.GlyphOffset.y = -2;
            }
            
            return ImGui::GetIO().Fonts->AddFontFromFileTTF(
                name, size, &fc);
        };

        // regular base
        ui_font_regular_base = load_font(
            "assets/fonts/Inter-Regular.ttf", 
            UISizes::text_base(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Regular.ttf", 
            UISizes::text_base(), 
            true
        );

        // regular xs
        ui_font_regular_xs = load_font(
            "assets/fonts/Inter-Regular.ttf", 
            UISizes::text_xs(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Regular.ttf", 
            UISizes::text_xs(), 
            true
        );

        // regular sm
        ui_font_regular_sm = load_font(
            "assets/fonts/Inter-Regular.ttf", 
            UISizes::text_sm(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Regular.ttf", 
            UISizes::text_sm(), 
            true
        );

        // regular lg
        ui_font_regular_lg = load_font(
            "assets/fonts/Inter-Regular.ttf", 
            UISizes::text_lg(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Regular.ttf", 
            UISizes::text_lg(), 
            true
        );

        // medium base
        ui_font_medium_base = load_font(
            "assets/fonts/Inter-Medium.ttf", 
            UISizes::text_base(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Medium.ttf", 
            UISizes::text_base(), 
            true
        );

        // medium xs
        ui_font_medium_xs = load_font(
            "assets/fonts/Inter-Medium.ttf", 
            UISizes::text_xs(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Medium.ttf", 
            UISizes::text_xs(), 
            true
        );

        // medium sm
        ui_font_medium_sm = load_font(
            "assets/fonts/Inter-Medium.ttf", 
            UISizes::text_sm(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Medium.ttf", 
            UISizes::text_sm(), 
            true
        );

        // medium lg
        ui_font_medium_lg = load_font(
            "assets/fonts/Inter-Medium.ttf", 
            UISizes::text_lg(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Medium.ttf", 
            UISizes::text_lg(), 
            true
        );

        // semibold base
        ui_font_semibold_base = load_font(
            "assets/fonts/Inter-SemiBold.ttf", 
            UISizes::text_base(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-SemiBold.ttf", 
            UISizes::text_base(), 
            true
        );

        // semibold xs
        ui_font_semibold_xs = load_font(
            "assets/fonts/Inter-SemiBold.ttf", 
            UISizes::text_xs(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-SemiBold.ttf", 
            UISizes::text_xs(), 
            true
        );

        // semibold sm
        ui_font_semibold_sm = load_font(
            "assets/fonts/Inter-SemiBold.ttf", 
            UISizes::text_sm(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-SemiBold.ttf", 
            UISizes::text_sm(), 
            true
        );

        // semibold lg
        ui_font_semibold_lg = load_font(
            "assets/fonts/Inter-SemiBold.ttf", 
            UISizes::text_lg(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-SemiBold.ttf", 
            UISizes::text_lg(), 
            true
        );

        // bold base
        ui_font_bold_base = load_font(
            "assets/fonts/Inter-Bold.ttf", 
            UISizes::text_base(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Bold.ttf", 
            UISizes::text_base(), 
            true
        );

        // bold xs
        ui_font_bold_xs = load_font(
            "assets/fonts/Inter-Bold.ttf", 
            UISizes::text_xs(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Bold.ttf", 
            UISizes::text_xs(), 
            true
        );

        // bold sm
        ui_font_bold_sm = load_font(
            "assets/fonts/Inter-Bold.ttf", 
            UISizes::text_sm(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Bold.ttf", 
            UISizes::text_sm(), 
            true
        );

        // bold lg
        ui_font_bold_lg = load_font(
            "assets/fonts/Inter-Bold.ttf", 
            UISizes::text_lg(), 
            false
        );
        load_font(
            "assets/fonts/NotoSansSC-Bold.ttf", 
            UISizes::text_lg(), 
            true
        );

        // icon font
        ui_font_icon = load_font(
            "assets/fonts/lucide.ttf", 
            UISizes::size_4(), 
            false
        );

        // icon font sm
        ui_font_icon_sm = load_font(
            "assets/fonts/lucide.ttf", 
            UISizes::size_3(), 
            false
        );

        return true;
    }

    ImFont * UIFont::font_regular_base() {
        return ui_font_regular_base;
    }

    ImFont * UIFont::font_regular_xs() {
        return ui_font_regular_xs;
    }

    ImFont * UIFont::font_regular_sm() {
        return ui_font_regular_sm;
    }

    ImFont * UIFont::font_regular_lg() {
        return ui_font_regular_lg;
    }

    ImFont * UIFont::font_medium_base() {
        return ui_font_medium_base;
    }

    ImFont * UIFont::font_medium_xs() {
        return ui_font_medium_xs;
    }

    ImFont * UIFont::font_medium_sm() {
        return ui_font_medium_sm;
    }

    ImFont * UIFont::font_medium_lg() {
        return ui_font_medium_lg;
    }

    ImFont * UIFont::font_semibold_base() {
        return ui_font_semibold_base;
    }

    ImFont * UIFont::font_semibold_xs() {
        return ui_font_semibold_xs;
    }

    ImFont * UIFont::font_semibold_sm() {
        return ui_font_semibold_sm;
    }

    ImFont * UIFont::font_semibold_lg() {
        return ui_font_semibold_lg;
    }

    ImFont * UIFont::font_bold_base() {
        return ui_font_bold_base;
    }

    ImFont * UIFont::font_bold_xs() {
        return ui_font_bold_xs;
    }

    ImFont * UIFont::font_bold_sm() {
        return ui_font_bold_sm;
    }

    ImFont * UIFont::font_bold_lg() {
        return ui_font_bold_lg;
    }

    ImFont * UIFont::font_icon() {
        return ui_font_icon;
    }

    ImFont * UIFont::font_icon_sm() {
        return ui_font_icon_sm;
    }
}