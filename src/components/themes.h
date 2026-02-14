#pragma once

#include "global.h"
#include "imgui.h"
#include <vector>

namespace ImModernUI {
    enum UIThemeScheme { 
        Light = 0, 
        Dark 
    };
    enum UIThemeBaseColor { 
        Blue = 0, 
        Green, 
        Netrual, 
        Amber, 
        Rose, 
        Purple, 
        Orange, 
        Teal, 
        Red, 
        Yellow, 
        Violet 
    };

    struct UIThemes {
        inline static UIThemeScheme current_scheme = UIThemeScheme::Light;
        inline static UIThemeBaseColor current_base_color = UIThemeBaseColor::Netrual;

        static void set_theme(UIThemeScheme s, UIThemeBaseColor b) {
            current_scheme = s;
            current_base_color = b;
        }

        static UIThemeScheme scheme() { return current_scheme; }
        static UIThemeBaseColor base_color() { return current_base_color; }

        static ImVec4 background() {
            return std::vector<ImVec4> {
                UIColors::color_white, UIColors::color_neutral_950,
            }[current_scheme];
        };
        static ImVec4 foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 card() {
            return std::vector<ImVec4> {
                UIColors::color_white, UIColors::color_neutral_900
            }[current_scheme];
        };
        static ImVec4 card_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 popover() {
            return std::vector<ImVec4> {
                UIColors::color_white, UIColors::color_neutral_800
            }[current_scheme];
        };
        static ImVec4 popover_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 primary() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_700, UIColors::color_blue_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_600, UIColors::color_lime_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_600, UIColors::color_amber_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_600, UIColors::color_rose_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_600, UIColors::color_purple_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_600, UIColors::color_orange_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_600, UIColors::color_teal_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_600, UIColors::color_red_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_400, UIColors::color_yellow_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_600, UIColors::color_violet_500
                }[current_scheme];
            }

            return std::vector<ImVec4> {
                UIColors::color_neutral_900, UIColors::color_neutral_200
            }[current_scheme];
        };
        static ImVec4 primary_foreground() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_50, UIColors::color_blue_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_50, UIColors::color_lime_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_50, UIColors::color_amber_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_50, UIColors::color_rose_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_50, UIColors::color_purple_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_50, UIColors::color_orange_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_50, UIColors::color_teal_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_50, UIColors::color_red_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_50, UIColors::color_yellow_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_50, UIColors::color_violet_50
                }[current_scheme];
            }

            return std::vector<ImVec4> {
                UIColors::color_neutral_50, UIColors::color_neutral_900
            }[current_scheme];
        };
        static ImVec4 secondary() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_100, UIColors::color_neutral_800
            }[current_scheme];
        };
        static ImVec4 secondary_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_900, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 muted() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_100, UIColors::color_neutral_800
            }[current_scheme];
        };
        static ImVec4 muted_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_500, UIColors::color_neutral_400
            }[current_scheme];
        };
        static ImVec4 accent() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_100, UIColors::color_neutral_700
            }[current_scheme];
        };
        static ImVec4 accent_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_900, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 destructive() {
            return std::vector<ImVec4> {
                UIColors::color_red_600, UIColors::color_red_400
            }[current_scheme];
        };
        static ImVec4 border() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_200, UIColors::color_white
            }[current_scheme];
        };
        static ImVec4 input() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_200, UIColors::color_white
            }[current_scheme];
        };
        static ImVec4 ring() {
            //if (current_base_color == UIThemeBaseColor::Blue) {
            //    return std::vector<ImVec4> {
            //        UIColors::color_blue_50, UIColors::color_blue_50
            //    }[current_scheme];
            //}
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_400, UIColors::color_lime_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_400, UIColors::color_amber_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_400, UIColors::color_rose_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_400, UIColors::color_purple_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_400, UIColors::color_orange_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_400, UIColors::color_teal_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_400, UIColors::color_red_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_400, UIColors::color_yellow_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_400, UIColors::color_violet_900
                }[current_scheme];
            }

            return std::vector<ImVec4> {
                UIColors::color_neutral_400, UIColors::color_neutral_500
            }[current_scheme];
        };
        static ImVec4 chart_1() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_300, UIColors::color_blue_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_300, UIColors::color_lime_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_300, UIColors::color_amber_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_300, UIColors::color_rose_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_300, UIColors::color_purple_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_300, UIColors::color_orange_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_300, UIColors::color_teal_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_300, UIColors::color_red_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_300, UIColors::color_yellow_300
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_300, UIColors::color_violet_300
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_blue_300, UIColors::color_blue_300
            }[current_scheme];
        };
        static ImVec4 chart_2() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_500, UIColors::color_blue_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_500, UIColors::color_lime_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_500, UIColors::color_amber_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_500, UIColors::color_rose_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_500, UIColors::color_purple_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_500, UIColors::color_orange_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_500, UIColors::color_teal_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_500, UIColors::color_red_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_500, UIColors::color_yellow_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_500, UIColors::color_violet_500
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_blue_500, UIColors::color_blue_500
            }[current_scheme];
        };
        static ImVec4 chart_3() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_600, UIColors::color_blue_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_600, UIColors::color_lime_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_600, UIColors::color_amber_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_600, UIColors::color_rose_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_600, UIColors::color_purple_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_600, UIColors::color_orange_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_600, UIColors::color_teal_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_600, UIColors::color_red_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_600, UIColors::color_yellow_600
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_600, UIColors::color_violet_600
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_blue_600, UIColors::color_blue_600
            }[current_scheme];
        };
        static ImVec4 chart_4() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_700, UIColors::color_blue_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_700, UIColors::color_lime_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_700, UIColors::color_amber_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_700, UIColors::color_rose_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_700, UIColors::color_purple_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_700, UIColors::color_orange_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_700, UIColors::color_teal_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_700, UIColors::color_red_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_700, UIColors::color_yellow_700
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_700, UIColors::color_violet_700
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_blue_700, UIColors::color_blue_700
            }[current_scheme];
        };
        static ImVec4 chart_5() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_800, UIColors::color_blue_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_800, UIColors::color_lime_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_800, UIColors::color_amber_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_800, UIColors::color_rose_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_800, UIColors::color_purple_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_800, UIColors::color_orange_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_800, UIColors::color_teal_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_800, UIColors::color_red_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_800, UIColors::color_yellow_800
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_800, UIColors::color_violet_800
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_blue_800, UIColors::color_blue_800
            }[current_scheme];
        };
        static ImVec4 sidebar() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_50, UIColors::color_neutral_900
            }[current_scheme];
        };
        static ImVec4 sidebar_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 sidebar_primary() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_600, UIColors::color_blue_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_600, UIColors::color_lime_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_600, UIColors::color_amber_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_600, UIColors::color_rose_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_600, UIColors::color_purple_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_600, UIColors::color_orange_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_600, UIColors::color_teal_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_600, UIColors::color_red_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_600, UIColors::color_yellow_500
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_600, UIColors::color_violet_500
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_neutral_900, UIColors::color_blue_700
            }[current_scheme];
        };
        static ImVec4 sidebar_primary_foreground() {
            if (current_base_color == UIThemeBaseColor::Blue) {
                return std::vector<ImVec4> {
                    UIColors::color_blue_50, UIColors::color_blue_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_50, UIColors::color_lime_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_50, UIColors::color_amber_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_50, UIColors::color_rose_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_50, UIColors::color_purple_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_50, UIColors::color_orange_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_50, UIColors::color_teal_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_50, UIColors::color_red_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_50, UIColors::color_yellow_50
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_50, UIColors::color_violet_50
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_neutral_50, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 sidebar_accent() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_100, UIColors::color_neutral_800
            }[current_scheme];
        };
        static ImVec4 sidebar_accent_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_900, UIColors::color_neutral_50
            }[current_scheme];
        };
        static ImVec4 sidebar_border() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_200, UIColors::color_white
            }[current_scheme];
        };
        static ImVec4 sidebar_ring() {
            //if (current_base_color == UIThemeBaseColor::Blue) {
            //    return std::vector<ImVec4> {
            //        UIColors::color_blue_400, UIColors::color_blue_900
            //    }[current_scheme];
            //}
            if (current_base_color == UIThemeBaseColor::Green) {
                return std::vector<ImVec4> {
                    UIColors::color_lime_400, UIColors::color_lime_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Amber) {
                return std::vector<ImVec4> {
                    UIColors::color_amber_400, UIColors::color_amber_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Rose) {
                return std::vector<ImVec4> {
                    UIColors::color_rose_400, UIColors::color_rose_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Purple) {
                return std::vector<ImVec4> {
                    UIColors::color_purple_400, UIColors::color_purple_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Orange) {
                return std::vector<ImVec4> {
                    UIColors::color_orange_400, UIColors::color_orange_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Teal) {
                return std::vector<ImVec4> {
                    UIColors::color_teal_400, UIColors::color_teal_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Red) {
                return std::vector<ImVec4> {
                    UIColors::color_red_400, UIColors::color_red_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Yellow) {
                return std::vector<ImVec4> {
                    UIColors::color_yellow_400, UIColors::color_yellow_900
                }[current_scheme];
            }
            if (current_base_color == UIThemeBaseColor::Violet) {
                return std::vector<ImVec4> {
                    UIColors::color_violet_400, UIColors::color_violet_900
                }[current_scheme];
            }
            return std::vector<ImVec4> {
                UIColors::color_neutral_400, UIColors::color_neutral_600
            }[current_scheme];
        };
        static ImVec4 surface() {
            return std::vector<ImVec4> {
                ImVec4(0.974, 0.974, 0.974, 1.000), 
                ImVec4(0.086, 0.086, 0.086, 1.000)
            }[current_scheme];
        };
        static ImVec4 surface_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_400
            }[current_scheme];
        };
        static ImVec4 code() {
            return std::vector<ImVec4> {
                ImVec4(0.974, 0.974, 0.974, 1.000), 
                ImVec4(0.086, 0.086, 0.086, 1.000)
            }[current_scheme];
        };
        static ImVec4 code_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_400
            }[current_scheme];
        };
        static ImVec4 code_highlight() {
            return std::vector<ImVec4> {
                ImVec4(0.948, 0.948, 0.948, 1.000), 
                ImVec4(0.150, 0.150, 0.150, 1.000)
            }[current_scheme];
        };
        static ImVec4 code_number() {
            return std::vector<ImVec4> {
                ImVec4(0.456, 0.456, 0.456, 1.000), 
                ImVec4(0.645, 0.645, 0.645, 1.000)
            }[current_scheme];
        };
        static ImVec4 selection() {
            return std::vector<ImVec4> {
                UIColors::color_neutral_950, UIColors::color_neutral_200
            }[current_scheme];
        };
        static ImVec4 selection_foreground() {
            return std::vector<ImVec4> {
                UIColors::color_white, UIColors::color_neutral_900
            }[current_scheme];
        };
        static ImVec4 overlay() {
            return ImVec4(0, 0, 0, 0.5);
        }
    };
}