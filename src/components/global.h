#pragma once

#include "imgui.h"
#include <string>

namespace ImModernUI {
    struct UISizes {
        inline static float base_font_size = 16.0;
        static void set_base_font_size(float size) { base_font_size = size; }
        
        static float spacing() { return 0.25 * base_font_size; }

        static float basis_3xs() { return 16 * base_font_size; }
        static float basis_2xs() { return 18 * base_font_size; }
        static float basis_xs() { return 20 * base_font_size; }
        static float basis_sm() { return 24 * base_font_size; }
        static float basis_md() { return 28 * base_font_size; }
        static float basis_lg() { return 32 * base_font_size; }
        static float basis_xl() { return 36 * base_font_size; }
        static float basis_2xl() { return 42 * base_font_size; }
        static float basis_3xl() { return 48 * base_font_size; }
        static float basis_4xl() { return 56 * base_font_size; }
        static float basis_5xl() { return 64 * base_font_size; }
        static float basis_6xl() { return 72 * base_font_size; }
        static float basis_7xl() { return 80 * base_font_size; }

        static float text_xs() { return 0.75 * base_font_size; }
        static float text_sm() { return 0.875 * base_font_size; }
        static float text_base() { return 1.0 * base_font_size; }
        static float text_lg() { return 1.125 * base_font_size; }
        static float text_xl() { return 1.25 * base_font_size; }
        static float text_2xl() { return 1.5 * base_font_size; }
        static float text_3xl() { return 1.875 * base_font_size; }
        static float text_4xl() { return 2.25 * base_font_size; }
        static float text_5xl() { return 3.0 * base_font_size; }
        static float text_6xl() { return 3.75 * base_font_size; }
        static float text_7xl() { return 4.5 * base_font_size; }
        static float text_8xl() { return 6.0 * base_font_size; }
        static float text_9xl() { return 8.0 * base_font_size; }
    
        static float rounded_xs() { return 0.625 * base_font_size - 6.0; }
        static float rounded_sm() { return 0.625 * base_font_size - 4.0; }
        static float rounded_md() { return 0.625 * base_font_size - 2.0; }
        static float rounded_lg() { return 0.625 * base_font_size; }
        static float rounded_xl() { return 0.625 * base_font_size + 4.0; }
        static float rounded_full() { return 9999.0; }

        #define PADDING_PARAM_LIST \
            PADDING(1) \
            PADDING(2) \
            PADDING(3) \
            PADDING(4) \
            PADDING(5) \
            PADDING(6) \
            PADDING(7) \
            PADDING(8) \
            PADDING(9) 
        #define PADDING(N) static float p_##N() { return N * spacing(); }
        PADDING_PARAM_LIST
        #undef PADDING

        #define MARGIN_PARAM_LIST \
            MARGIN(1) \
            MARGIN(2) \
            MARGIN(3) \
            MARGIN(4) \
            MARGIN(5) \
            MARGIN(6) \
            MARGIN(7) \
            MARGIN(8) \
            MARGIN(9) 
        #define MARGIN(N) static float m_##N() { return N * spacing(); }
        MARGIN_PARAM_LIST
        #undef MARGIN

        #define HEIGHT_PARAM_LIST \
            HEIGHT(1) \
            HEIGHT(2) \
            HEIGHT(3) \
            HEIGHT(4) \
            HEIGHT(5) \
            HEIGHT(6) \
            HEIGHT(7) \
            HEIGHT(8) \
            HEIGHT(9) \
            HEIGHT(10) \
            HEIGHT(16) \
            HEIGHT(24) \
            HEIGHT(32) \
            HEIGHT(44) \
            HEIGHT(64) \
            HEIGHT(72)
        #define HEIGHT(N) static float h_##N() { return N * spacing(); }
        HEIGHT_PARAM_LIST
        #undef HEIGHT

        #define WIDTH_PARAM_LIST \
            WIDTH(1) \
            WIDTH(2) \
            WIDTH(3) \
            WIDTH(4) \
            WIDTH(5) \
            WIDTH(6) \
            WIDTH(7) \
            WIDTH(8) \
            WIDTH(9) \
            WIDTH(10) \
            WIDTH(16) \
            WIDTH(18) \
            WIDTH(20) \
            WIDTH(24) \
            WIDTH(26) \
            WIDTH(28) \
            WIDTH(32) \
            WIDTH(48) \
            WIDTH(72) \
            WIDTH(96)
        #define WIDTH(N) static float w_##N() { return N * spacing(); }
        WIDTH_PARAM_LIST
        #undef WIDTH
        static float w_lg() { return 32.0 * base_font_size; }

        #define BORDER_PARAM_LIST \
            BORDER(0) \
            BORDER(1) \
            BORDER(2) 
        #define BORDER(N) static float border_##N() { return N * 1.0; }
        BORDER_PARAM_LIST
        #undef BORDER

        #define SIZE_PARAM_LIST \
            SIZE(0) \
            SIZE(1) \
            SIZE(2) \
            SIZE(3) \
            SIZE(4) \
            SIZE(6) \
            SIZE(8)
        #define SIZE(N) static float size_##N() { return N * spacing(); }
        SIZE_PARAM_LIST
        #undef SIZE
        
        #define UNDERLINE_OFFSET_PARAM_LIST \
            UNDERLINE_OFFSET(1) \
            UNDERLINE_OFFSET(2) \
            UNDERLINE_OFFSET(4) \
            UNDERLINE_OFFSET(8)
        #define UNDERLINE_OFFSET(N) static float underline_offset_##N() { return N; }
        UNDERLINE_OFFSET_PARAM_LIST
        #undef UNDERLINE_OFFSET
        
    };

    struct UIColors {
        static constexpr ImVec4 color_red_50 = ImVec4(0.997, 0.950, 0.950, 1.000);
        static constexpr ImVec4 color_red_100 = ImVec4(0.999, 0.886, 0.886, 1.000);
        static constexpr ImVec4 color_red_200 = ImVec4(1.000, 0.790, 0.790, 1.000);
        static constexpr ImVec4 color_red_300 = ImVec4(1.000, 0.635, 0.636, 1.000);
        static constexpr ImVec4 color_red_400 = ImVec4(1.000, 0.391, 0.404, 1.000);
        static constexpr ImVec4 color_red_500 = ImVec4(0.983, 0.172, 0.213, 1.000);
        static constexpr ImVec4 color_red_600 = ImVec4(0.906, 0.000, 0.042, 1.000);
        static constexpr ImVec4 color_red_700 = ImVec4(0.757, 0.000, 0.029, 1.000);
        static constexpr ImVec4 color_red_800 = ImVec4(0.622, 0.029, 0.069, 1.000);
        static constexpr ImVec4 color_red_900 = ImVec4(0.509, 0.092, 0.101, 1.000);
        static constexpr ImVec4 color_red_950 = ImVec4(0.275, 0.032, 0.034, 1.000);

        static constexpr ImVec4 color_orange_50 = ImVec4(1.000, 0.969, 0.929, 1.000);
        static constexpr ImVec4 color_orange_100 = ImVec4(1.000, 0.929, 0.833, 1.000);
        static constexpr ImVec4 color_orange_200 = ImVec4(1.000, 0.841, 0.657, 1.000);
        static constexpr ImVec4 color_orange_300 = ImVec4(1.000, 0.722, 0.414, 1.000);
        static constexpr ImVec4 color_orange_400 = ImVec4(1.000, 0.537, 0.014, 1.000);
        static constexpr ImVec4 color_orange_500 = ImVec4(1.000, 0.411, 0.000, 1.000);
        static constexpr ImVec4 color_orange_600 = ImVec4(0.961, 0.288, 0.000, 1.000);
        static constexpr ImVec4 color_orange_700 = ImVec4(0.792, 0.207, 0.000, 1.000);
        static constexpr ImVec4 color_orange_800 = ImVec4(0.624, 0.177, 0.000, 1.000);
        static constexpr ImVec4 color_orange_900 = ImVec4(0.495, 0.165, 0.046, 1.000);
        static constexpr ImVec4 color_orange_950 = ImVec4(0.266, 0.074, 0.022, 1.000);

        static constexpr ImVec4 color_amber_50 = ImVec4(1.000, 0.985, 0.920, 1.000);
        static constexpr ImVec4 color_amber_100 = ImVec4(0.997, 0.953, 0.778, 1.000);
        static constexpr ImVec4 color_amber_200 = ImVec4(0.996, 0.901, 0.522, 1.000);
        static constexpr ImVec4 color_amber_300 = ImVec4(1.000, 0.824, 0.188, 1.000);
        static constexpr ImVec4 color_amber_400 = ImVec4(1.000, 0.727, 0.000, 1.000);
        static constexpr ImVec4 color_amber_500 = ImVec4(0.994, 0.602, 0.000, 1.000);
        static constexpr ImVec4 color_amber_600 = ImVec4(0.884, 0.443, 0.000, 1.000);
        static constexpr ImVec4 color_amber_700 = ImVec4(0.732, 0.301, 0.000, 1.000);
        static constexpr ImVec4 color_amber_800 = ImVec4(0.590, 0.234, 0.000, 1.000);
        static constexpr ImVec4 color_amber_900 = ImVec4(0.480, 0.200, 0.025, 1.000);
        static constexpr ImVec4 color_amber_950 = ImVec4(0.274, 0.098, 0.005, 1.000);
    
        static constexpr ImVec4 color_yellow_50 = ImVec4(0.996, 0.988, 0.910, 1.000);
        static constexpr ImVec4 color_yellow_100 = ImVec4(0.997, 0.977, 0.760, 1.000);
        static constexpr ImVec4 color_yellow_200 = ImVec4(0.999, 0.941, 0.523, 1.000);
        static constexpr ImVec4 color_yellow_300 = ImVec4(1.000, 0.876, 0.126, 1.000);
        static constexpr ImVec4 color_yellow_400 = ImVec4(0.993, 0.782, 0.000, 1.000);
        static constexpr ImVec4 color_yellow_500 = ImVec4(0.941, 0.693, 0.000, 1.000);
        static constexpr ImVec4 color_yellow_600 = ImVec4(0.818, 0.530, 0.000, 1.000);
        static constexpr ImVec4 color_yellow_700 = ImVec4(0.651, 0.373, 0.000, 1.000);
        static constexpr ImVec4 color_yellow_800 = ImVec4(0.536, 0.293, 0.000, 1.000);
        static constexpr ImVec4 color_yellow_900 = ImVec4(0.450, 0.242, 0.041, 1.000);
        static constexpr ImVec4 color_yellow_950 = ImVec4(0.262, 0.124, 0.017, 1.000);
    
        static constexpr ImVec4 color_lime_50 = ImVec4(0.969, 0.997, 0.906, 1.000);
        static constexpr ImVec4 color_lime_100 = ImVec4(0.925, 0.989, 0.793, 1.000);
        static constexpr ImVec4 color_lime_200 = ImVec4(0.848, 0.978, 0.600, 1.000);
        static constexpr ImVec4 color_lime_300 = ImVec4(0.733, 0.955, 0.318, 1.000);
        static constexpr ImVec4 color_lime_400 = ImVec4(0.602, 0.902, 0.000, 1.000);
        static constexpr ImVec4 color_lime_500 = ImVec4(0.487, 0.810, 0.000, 1.000);
        static constexpr ImVec4 color_lime_600 = ImVec4(0.369, 0.647, 0.000, 1.000);
        static constexpr ImVec4 color_lime_700 = ImVec4(0.285, 0.492, 0.000, 1.000);
        static constexpr ImVec4 color_lime_800 = ImVec4(0.237, 0.388, 0.000, 1.000);
        static constexpr ImVec4 color_lime_900 = ImVec4(0.207, 0.327, 0.055, 1.000);
        static constexpr ImVec4 color_lime_950 = ImVec4(0.099, 0.181, 0.011, 1.000);
    
        static constexpr ImVec4 color_green_50 = ImVec4(0.941, 0.992, 0.957, 1.000);
        static constexpr ImVec4 color_green_100 = ImVec4(0.861, 0.988, 0.905, 1.000);
        static constexpr ImVec4 color_green_200 = ImVec4(0.725, 0.971, 0.812, 1.000);
        static constexpr ImVec4 color_green_300 = ImVec4(0.481, 0.946, 0.657, 1.000);
        static constexpr ImVec4 color_green_400 = ImVec4(0.020, 0.875, 0.449, 1.000);
        static constexpr ImVec4 color_green_500 = ImVec4(0.000, 0.787, 0.316, 1.000);
        static constexpr ImVec4 color_green_600 = ImVec4(0.000, 0.651, 0.242, 1.000);
        static constexpr ImVec4 color_green_700 = ImVec4(0.000, 0.510, 0.210, 1.000);
        static constexpr ImVec4 color_green_800 = ImVec4(0.006, 0.401, 0.189, 1.000);
        static constexpr ImVec4 color_green_900 = ImVec4(0.051, 0.329, 0.170, 1.000);
        static constexpr ImVec4 color_green_950 = ImVec4(0.012, 0.181, 0.084, 1.000);
    
        static constexpr ImVec4 color_emerald_50 = ImVec4(0.924, 0.992, 0.960, 1.000);
        static constexpr ImVec4 color_emerald_100 = ImVec4(0.816, 0.981, 0.897, 1.000);
        static constexpr ImVec4 color_emerald_200 = ImVec4(0.644, 0.956, 0.813, 1.000);
        static constexpr ImVec4 color_emerald_300 = ImVec4(0.370, 0.915, 0.709, 1.000);
        static constexpr ImVec4 color_emerald_400 = ImVec4(0.000, 0.833, 0.572, 1.000);
        static constexpr ImVec4 color_emerald_500 = ImVec4(0.000, 0.739, 0.489, 1.000);
        static constexpr ImVec4 color_emerald_600 = ImVec4(0.000, 0.599, 0.399, 1.000);
        static constexpr ImVec4 color_emerald_700 = ImVec4(0.000, 0.478, 0.334, 1.000);
        static constexpr ImVec4 color_emerald_800 = ImVec4(0.000, 0.378, 0.271, 1.000);
        static constexpr ImVec4 color_emerald_900 = ImVec4(0.000, 0.308, 0.230, 1.000);
        static constexpr ImVec4 color_emerald_950 = ImVec4(0.000, 0.174, 0.133, 1.000);
    
        static constexpr ImVec4 color_teal_50 = ImVec4(0.942, 0.993, 0.981, 1.000);
        static constexpr ImVec4 color_teal_100 = ImVec4(0.797, 0.986, 0.946, 1.000);
        static constexpr ImVec4 color_teal_200 = ImVec4(0.587, 0.967, 0.895, 1.000);
        static constexpr ImVec4 color_teal_300 = ImVec4(0.276, 0.927, 0.834, 1.000);
        static constexpr ImVec4 color_teal_400 = ImVec4(0.000, 0.835, 0.743, 1.000);
        static constexpr ImVec4 color_teal_500 = ImVec4(0.000, 0.733, 0.655, 1.000);
        static constexpr ImVec4 color_teal_600 = ImVec4(0.000, 0.589, 0.537, 1.000);
        static constexpr ImVec4 color_teal_700 = ImVec4(0.000, 0.469, 0.435, 1.000);
        static constexpr ImVec4 color_teal_800 = ImVec4(0.000, 0.373, 0.352, 1.000);
        static constexpr ImVec4 color_teal_900 = ImVec4(0.042, 0.308, 0.292, 1.000);
        static constexpr ImVec4 color_teal_950 = ImVec4(0.008, 0.185, 0.181, 1.000);
    
        static constexpr ImVec4 color_cyan_50 = ImVec4(0.925, 0.996, 1.000, 1.000);
        static constexpr ImVec4 color_cyan_100 = ImVec4(0.809, 0.981, 0.997, 1.000);
        static constexpr ImVec4 color_cyan_200 = ImVec4(0.637, 0.955, 0.992, 1.000);
        static constexpr ImVec4 color_cyan_300 = ImVec4(0.327, 0.917, 0.991, 1.000);
        static constexpr ImVec4 color_cyan_400 = ImVec4(0.000, 0.827, 0.951, 1.000);
        static constexpr ImVec4 color_cyan_500 = ImVec4(0.000, 0.722, 0.857, 1.000);
        static constexpr ImVec4 color_cyan_600 = ImVec4(0.000, 0.574, 0.723, 1.000);
        static constexpr ImVec4 color_cyan_700 = ImVec4(0.000, 0.459, 0.583, 1.000);
        static constexpr ImVec4 color_cyan_800 = ImVec4(0.000, 0.371, 0.471, 1.000);
        static constexpr ImVec4 color_cyan_900 = ImVec4(0.064, 0.307, 0.394, 1.000);
        static constexpr ImVec4 color_cyan_950 = ImVec4(0.021, 0.201, 0.270, 1.000);
    
        static constexpr ImVec4 color_sky_50 = ImVec4(0.940, 0.977, 1.000, 1.000);
        static constexpr ImVec4 color_sky_100 = ImVec4(0.876, 0.949, 0.998, 1.000);
        static constexpr ImVec4 color_sky_200 = ImVec4(0.722, 0.903, 0.997, 1.000);
        static constexpr ImVec4 color_sky_300 = ImVec4(0.453, 0.832, 1.000, 1.000);
        static constexpr ImVec4 color_sky_400 = ImVec4(0.000, 0.736, 1.000, 1.000);
        static constexpr ImVec4 color_sky_500 = ImVec4(0.000, 0.650, 0.957, 1.000);
        static constexpr ImVec4 color_sky_600 = ImVec4(0.000, 0.518, 0.820, 1.000);
        static constexpr ImVec4 color_sky_700 = ImVec4(0.000, 0.412, 0.660, 1.000);
        static constexpr ImVec4 color_sky_800 = ImVec4(0.000, 0.349, 0.540, 1.000);
        static constexpr ImVec4 color_sky_900 = ImVec4(0.007, 0.290, 0.441, 1.000);
        static constexpr ImVec4 color_sky_950 = ImVec4(0.020, 0.184, 0.291, 1.000);
    
        static constexpr ImVec4 color_blue_50 = ImVec4(0.937, 0.964, 0.999, 1.000);
        static constexpr ImVec4 color_blue_100 = ImVec4(0.858, 0.918, 0.997, 1.000);
        static constexpr ImVec4 color_blue_200 = ImVec4(0.745, 0.859, 1.000, 1.000);
        static constexpr ImVec4 color_blue_300 = ImVec4(0.557, 0.773, 1.000, 1.000);
        static constexpr ImVec4 color_blue_400 = ImVec4(0.316, 0.636, 1.000, 1.000);
        static constexpr ImVec4 color_blue_500 = ImVec4(0.169, 0.498, 1.000, 1.000);
        static constexpr ImVec4 color_blue_600 = ImVec4(0.084, 0.364, 0.986, 1.000);
        static constexpr ImVec4 color_blue_700 = ImVec4(0.078, 0.279, 0.902, 1.000);
        static constexpr ImVec4 color_blue_800 = ImVec4(0.100, 0.234, 0.723, 1.000);
        static constexpr ImVec4 color_blue_900 = ImVec4(0.109, 0.222, 0.558, 1.000);
        static constexpr ImVec4 color_blue_950 = ImVec4(0.087, 0.143, 0.336, 1.000);
    
        static constexpr ImVec4 color_indigo_50 = ImVec4(0.933, 0.949, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_100 = ImVec4(0.878, 0.906, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_200 = ImVec4(0.778, 0.823, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_300 = ImVec4(0.639, 0.702, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_400 = ImVec4(0.488, 0.527, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_500 = ImVec4(0.382, 0.372, 1.000, 1.000);
        static constexpr ImVec4 color_indigo_600 = ImVec4(0.311, 0.224, 0.966, 1.000);
        static constexpr ImVec4 color_indigo_700 = ImVec4(0.264, 0.177, 0.845, 1.000);
        static constexpr ImVec4 color_indigo_800 = ImVec4(0.215, 0.163, 0.674, 1.000);
        static constexpr ImVec4 color_indigo_900 = ImVec4(0.192, 0.173, 0.523, 1.000);
        static constexpr ImVec4 color_indigo_950 = ImVec4(0.117, 0.103, 0.301, 1.000);
    
        static constexpr ImVec4 color_violet_50 = ImVec4(0.961, 0.953, 1.000, 1.000);
        static constexpr ImVec4 color_violet_100 = ImVec4(0.929, 0.913, 0.997, 1.000);
        static constexpr ImVec4 color_violet_200 = ImVec4(0.867, 0.838, 1.000, 1.000);
        static constexpr ImVec4 color_violet_300 = ImVec4(0.770, 0.704, 1.000, 1.000);
        static constexpr ImVec4 color_violet_400 = ImVec4(0.653, 0.517, 1.000, 1.000);
        static constexpr ImVec4 color_violet_500 = ImVec4(0.556, 0.318, 1.000, 1.000);
        static constexpr ImVec4 color_violet_600 = ImVec4(0.500, 0.134, 0.996, 1.000);
        static constexpr ImVec4 color_violet_700 = ImVec4(0.440, 0.031, 0.906, 1.000);
        static constexpr ImVec4 color_violet_800 = ImVec4(0.365, 0.056, 0.753, 1.000);
        static constexpr ImVec4 color_violet_900 = ImVec4(0.302, 0.089, 0.604, 1.000);
        static constexpr ImVec4 color_violet_950 = ImVec4(0.183, 0.051, 0.406, 1.000);
    
        static constexpr ImVec4 color_purple_50 = ImVec4(0.980, 0.961, 1.000, 1.000);
        static constexpr ImVec4 color_purple_100 = ImVec4(0.953, 0.909, 1.000, 1.000);
        static constexpr ImVec4 color_purple_200 = ImVec4(0.915, 0.833, 1.000, 1.000);
        static constexpr ImVec4 color_purple_300 = ImVec4(0.854, 0.698, 1.000, 1.000);
        static constexpr ImVec4 color_purple_400 = ImVec4(0.760, 0.480, 1.000, 1.000);
        static constexpr ImVec4 color_purple_500 = ImVec4(0.678, 0.276, 1.000, 1.000);
        static constexpr ImVec4 color_purple_600 = ImVec4(0.597, 0.062, 0.981, 1.000);
        static constexpr ImVec4 color_purple_700 = ImVec4(0.510, 0.000, 0.857, 1.000);
        static constexpr ImVec4 color_purple_800 = ImVec4(0.430, 0.067, 0.691, 1.000);
        static constexpr ImVec4 color_purple_900 = ImVec4(0.351, 0.087, 0.545, 1.000);
        static constexpr ImVec4 color_purple_950 = ImVec4(0.235, 0.012, 0.401, 1.000);
    
        static constexpr ImVec4 color_fuchsia_50 = ImVec4(0.991, 0.957, 0.999, 1.000);
        static constexpr ImVec4 color_fuchsia_100 = ImVec4(0.982, 0.909, 1.000, 1.000);
        static constexpr ImVec4 color_fuchsia_200 = ImVec4(0.964, 0.813, 1.000, 1.000);
        static constexpr ImVec4 color_fuchsia_300 = ImVec4(0.955, 0.657, 1.000, 1.000);
        static constexpr ImVec4 color_fuchsia_400 = ImVec4(0.930, 0.418, 1.000, 1.000);
        static constexpr ImVec4 color_fuchsia_500 = ImVec4(0.884, 0.166, 0.985, 1.000);
        static constexpr ImVec4 color_fuchsia_600 = ImVec4(0.784, 0.000, 0.872, 1.000);
        static constexpr ImVec4 color_fuchsia_700 = ImVec4(0.658, 0.000, 0.718, 1.000);
        static constexpr ImVec4 color_fuchsia_800 = ImVec4(0.541, 0.005, 0.582, 1.000);
        static constexpr ImVec4 color_fuchsia_900 = ImVec4(0.448, 0.075, 0.470, 1.000);
        static constexpr ImVec4 color_fuchsia_950 = ImVec4(0.294, 0.001, 0.311, 1.000);
    
        static constexpr ImVec4 color_pink_50 = ImVec4(0.991, 0.949, 0.972, 1.000);
        static constexpr ImVec4 color_pink_100 = ImVec4(0.989, 0.905, 0.953, 1.000);
        static constexpr ImVec4 color_pink_200 = ImVec4(0.988, 0.809, 0.911, 1.000);
        static constexpr ImVec4 color_pink_300 = ImVec4(0.994, 0.646, 0.837, 1.000);
        static constexpr ImVec4 color_pink_400 = ImVec4(0.986, 0.392, 0.714, 1.000);
        static constexpr ImVec4 color_pink_500 = ImVec4(0.966, 0.198, 0.604, 1.000);
        static constexpr ImVec4 color_pink_600 = ImVec4(0.901, 0.000, 0.463, 1.000);
        static constexpr ImVec4 color_pink_700 = ImVec4(0.778, 0.000, 0.359, 1.000);
        static constexpr ImVec4 color_pink_800 = ImVec4(0.639, 0.000, 0.298, 1.000);
        static constexpr ImVec4 color_pink_900 = ImVec4(0.525, 0.063, 0.261, 1.000);
        static constexpr ImVec4 color_pink_950 = ImVec4(0.318, 0.015, 0.140, 1.000);
    
        static constexpr ImVec4 color_rose_50 = ImVec4(0.999, 0.945, 0.949, 1.000);
        static constexpr ImVec4 color_rose_100 = ImVec4(1.000, 0.893, 0.901, 1.000);
        static constexpr ImVec4 color_rose_200 = ImVec4(1.000, 0.801, 0.826, 1.000);
        static constexpr ImVec4 color_rose_300 = ImVec4(1.000, 0.630, 0.680, 1.000);
        static constexpr ImVec4 color_rose_400 = ImVec4(1.000, 0.389, 0.494, 1.000);
        static constexpr ImVec4 color_rose_500 = ImVec4(1.000, 0.125, 0.339, 1.000);
        static constexpr ImVec4 color_rose_600 = ImVec4(0.927, 0.000, 0.249, 1.000);
        static constexpr ImVec4 color_rose_700 = ImVec4(0.779, 0.000, 0.211, 1.000);
        static constexpr ImVec4 color_rose_800 = ImVec4(0.647, 0.000, 0.212, 1.000);
        static constexpr ImVec4 color_rose_900 = ImVec4(0.545, 0.030, 0.211, 1.000);
        static constexpr ImVec4 color_rose_950 = ImVec4(0.303, 0.009, 0.096, 1.000);
    
        static constexpr ImVec4 color_slate_50 = ImVec4(0.973, 0.980, 0.987, 1.000);
        static constexpr ImVec4 color_slate_100 = ImVec4(0.944, 0.960, 0.977, 1.000);
        static constexpr ImVec4 color_slate_200 = ImVec4(0.886, 0.910, 0.943, 1.000);
        static constexpr ImVec4 color_slate_300 = ImVec4(0.792, 0.836, 0.888, 1.000);
        static constexpr ImVec4 color_slate_400 = ImVec4(0.565, 0.632, 0.725, 1.000);
        static constexpr ImVec4 color_slate_500 = ImVec4(0.384, 0.455, 0.557, 1.000);
        static constexpr ImVec4 color_slate_600 = ImVec4(0.271, 0.334, 0.424, 1.000);
        static constexpr ImVec4 color_slate_700 = ImVec4(0.194, 0.255, 0.343, 1.000);
        static constexpr ImVec4 color_slate_800 = ImVec4(0.112, 0.160, 0.239, 1.000);
        static constexpr ImVec4 color_slate_900 = ImVec4(0.057, 0.090, 0.169, 1.000);
        static constexpr ImVec4 color_slate_950 = ImVec4(0.007, 0.023, 0.093, 1.000);
    
        static constexpr ImVec4 color_gray_50 = ImVec4(0.976, 0.981, 0.986, 1.000);
        static constexpr ImVec4 color_gray_100 = ImVec4(0.953, 0.957, 0.965, 1.000);
        static constexpr ImVec4 color_gray_200 = ImVec4(0.898, 0.906, 0.923, 1.000);
        static constexpr ImVec4 color_gray_300 = ImVec4(0.819, 0.836, 0.861, 1.000);
        static constexpr ImVec4 color_gray_400 = ImVec4(0.600, 0.631, 0.685, 1.000);
        static constexpr ImVec4 color_gray_500 = ImVec4(0.415, 0.447, 0.510, 1.000);
        static constexpr ImVec4 color_gray_600 = ImVec4(0.289, 0.334, 0.396, 1.000);
        static constexpr ImVec4 color_gray_700 = ImVec4(0.212, 0.255, 0.325, 1.000);
        static constexpr ImVec4 color_gray_800 = ImVec4(0.117, 0.161, 0.222, 1.000);
        static constexpr ImVec4 color_gray_900 = ImVec4(0.065, 0.094, 0.157, 1.000);
        static constexpr ImVec4 color_gray_950 = ImVec4(0.012, 0.028, 0.072, 1.000);
    
        static constexpr ImVec4 color_zinc_50 = ImVec4(0.980, 0.980, 0.980, 1.000);
        static constexpr ImVec4 color_zinc_100 = ImVec4(0.956, 0.956, 0.959, 1.000);
        static constexpr ImVec4 color_zinc_200 = ImVec4(0.894, 0.894, 0.906, 1.000);
        static constexpr ImVec4 color_zinc_300 = ImVec4(0.831, 0.831, 0.848, 1.000);
        static constexpr ImVec4 color_zinc_400 = ImVec4(0.623, 0.623, 0.663, 1.000);
        static constexpr ImVec4 color_zinc_500 = ImVec4(0.443, 0.443, 0.484, 1.000);
        static constexpr ImVec4 color_zinc_600 = ImVec4(0.321, 0.321, 0.362, 1.000);
        static constexpr ImVec4 color_zinc_700 = ImVec4(0.246, 0.246, 0.276, 1.000);
        static constexpr ImVec4 color_zinc_800 = ImVec4(0.153, 0.153, 0.166, 1.000);
        static constexpr ImVec4 color_zinc_900 = ImVec4(0.094, 0.094, 0.106, 1.000);
        static constexpr ImVec4 color_zinc_950 = ImVec4(0.035, 0.035, 0.044, 1.000);
    
        static constexpr ImVec4 color_neutral_50 = ImVec4(0.980, 0.980, 0.980, 1.000);
        static constexpr ImVec4 color_neutral_100 = ImVec4(0.961, 0.961, 0.961, 1.000);
        static constexpr ImVec4 color_neutral_200 = ImVec4(0.898, 0.898, 0.898, 1.000);
        static constexpr ImVec4 color_neutral_300 = ImVec4(0.831, 0.831, 0.831, 1.000);
        static constexpr ImVec4 color_neutral_400 = ImVec4(0.630, 0.630, 0.630, 1.000);
        static constexpr ImVec4 color_neutral_500 = ImVec4(0.452, 0.452, 0.452, 1.000);
        static constexpr ImVec4 color_neutral_600 = ImVec4(0.322, 0.322, 0.322, 1.000);
        static constexpr ImVec4 color_neutral_700 = ImVec4(0.250, 0.250, 0.250, 1.000);
        static constexpr ImVec4 color_neutral_800 = ImVec4(0.149, 0.149, 0.149, 1.000);
        static constexpr ImVec4 color_neutral_900 = ImVec4(0.091, 0.091, 0.091, 1.000);
        static constexpr ImVec4 color_neutral_950 = ImVec4(0.039, 0.039, 0.039, 1.000);
    
        static constexpr ImVec4 color_stone_50 = ImVec4(0.981, 0.981, 0.978, 1.000);
        static constexpr ImVec4 color_stone_100 = ImVec4(0.961, 0.961, 0.958, 1.000);
        static constexpr ImVec4 color_stone_200 = ImVec4(0.907, 0.898, 0.893, 1.000);
        static constexpr ImVec4 color_stone_300 = ImVec4(0.841, 0.828, 0.818, 1.000);
        static constexpr ImVec4 color_stone_400 = ImVec4(0.652, 0.626, 0.609, 1.000);
        static constexpr ImVec4 color_stone_500 = ImVec4(0.473, 0.442, 0.420, 1.000);
        static constexpr ImVec4 color_stone_600 = ImVec4(0.343, 0.325, 0.302, 1.000);
        static constexpr ImVec4 color_stone_700 = ImVec4(0.268, 0.250, 0.232, 1.000);
        static constexpr ImVec4 color_stone_800 = ImVec4(0.162, 0.144, 0.140, 1.000);
        static constexpr ImVec4 color_stone_900 = ImVec4(0.110, 0.098, 0.090, 1.000);
        static constexpr ImVec4 color_stone_950 = ImVec4(0.047, 0.039, 0.036, 1.000);

        static constexpr ImVec4 color_black = ImVec4(0.000, 0.000, 0.000, 1.000);
        static constexpr ImVec4 color_white = ImVec4(1.000, 1.000, 1.000, 1.000);
        static constexpr ImVec4 color_transparent = ImVec4(0.000, 0.000, 0.000, 0.000);

        static ImVec4 color(const std::string& col) {
            if (col == "red_50") return color_red_50;
            if (col == "red_100") return color_red_100;
            if (col == "red_200") return color_red_200;
            if (col == "red_300") return color_red_300;
            if (col == "red_400") return color_red_400;
            if (col == "red_500") return color_red_500;
            if (col == "red_600") return color_red_600;
            if (col == "red_700") return color_red_700;
            if (col == "red_800") return color_red_800;
            if (col == "red_900") return color_red_900;
            if (col == "red_950") return color_red_950;

            if (col == "orange_50") return color_orange_50;
            if (col == "orange_100") return color_orange_100;
            if (col == "orange_200") return color_orange_200;
            if (col == "orange_300") return color_orange_300;
            if (col == "orange_400") return color_orange_400;
            if (col == "orange_500") return color_orange_500;
            if (col == "orange_600") return color_orange_600;
            if (col == "orange_700") return color_orange_700;
            if (col == "orange_800") return color_orange_800;
            if (col == "orange_900") return color_orange_900;
            if (col == "orange_950") return color_orange_950;

            if (col == "amber_50") return color_amber_50;
            if (col == "amber_100") return color_amber_100;
            if (col == "amber_200") return color_amber_200;
            if (col == "amber_300") return color_amber_300;
            if (col == "amber_400") return color_amber_400;
            if (col == "amber_500") return color_amber_500;
            if (col == "amber_600") return color_amber_600;
            if (col == "amber_700") return color_amber_700;
            if (col == "amber_800") return color_amber_800;
            if (col == "amber_900") return color_amber_900;
            if (col == "amber_950") return color_amber_950;

            if (col == "yellow_50") return color_yellow_50;
            if (col == "yellow_100") return color_yellow_100;
            if (col == "yellow_200") return color_yellow_200;
            if (col == "yellow_300") return color_yellow_300;
            if (col == "yellow_400") return color_yellow_400;
            if (col == "yellow_500") return color_yellow_500;
            if (col == "yellow_600") return color_yellow_600;
            if (col == "yellow_700") return color_yellow_700;
            if (col == "yellow_800") return color_yellow_800;
            if (col == "yellow_900") return color_yellow_900;
            if (col == "yellow_950") return color_yellow_950;

            if (col == "lime_50") return color_lime_50;
            if (col == "lime_100") return color_lime_100;
            if (col == "lime_200") return color_lime_200;
            if (col == "lime_300") return color_lime_300;
            if (col == "lime_400") return color_lime_400;
            if (col == "lime_500") return color_lime_500;
            if (col == "lime_600") return color_lime_600;
            if (col == "lime_700") return color_lime_700;
            if (col == "lime_800") return color_lime_800;
            if (col == "lime_900") return color_lime_900;
            if (col == "lime_950") return color_lime_950;

            if (col == "green_50") return color_green_50;
            if (col == "green_100") return color_green_100;
            if (col == "green_200") return color_green_200;
            if (col == "green_300") return color_green_300;
            if (col == "green_400") return color_green_400;
            if (col == "green_500") return color_green_500;
            if (col == "green_600") return color_green_600;
            if (col == "green_700") return color_green_700;
            if (col == "green_800") return color_green_800;
            if (col == "green_900") return color_green_900;
            if (col == "green_950") return color_green_950;

            if (col == "emerald_50") return color_emerald_50;
            if (col == "emerald_100") return color_emerald_100;
            if (col == "emerald_200") return color_emerald_200;
            if (col == "emerald_300") return color_emerald_300;
            if (col == "emerald_400") return color_emerald_400;
            if (col == "emerald_500") return color_emerald_500;
            if (col == "emerald_600") return color_emerald_600;
            if (col == "emerald_700") return color_emerald_700;
            if (col == "emerald_800") return color_emerald_800;
            if (col == "emerald_900") return color_emerald_900;
            if (col == "emerald_950") return color_emerald_950;

            if (col == "teal_50") return color_teal_50;
            if (col == "teal_100") return color_teal_100;
            if (col == "teal_200") return color_teal_200;
            if (col == "teal_300") return color_teal_300;
            if (col == "teal_400") return color_teal_400;
            if (col == "teal_500") return color_teal_500;
            if (col == "teal_600") return color_teal_600;
            if (col == "teal_700") return color_teal_700;
            if (col == "teal_800") return color_teal_800;
            if (col == "teal_900") return color_teal_900;
            if (col == "teal_950") return color_teal_950;

            if (col == "cyan_50") return color_cyan_50;
            if (col == "cyan_100") return color_cyan_100;
            if (col == "cyan_200") return color_cyan_200;
            if (col == "cyan_300") return color_cyan_300;
            if (col == "cyan_400") return color_cyan_400;
            if (col == "cyan_500") return color_cyan_500;
            if (col == "cyan_600") return color_cyan_600;
            if (col == "cyan_700") return color_cyan_700;
            if (col == "cyan_800") return color_cyan_800;
            if (col == "cyan_900") return color_cyan_900;
            if (col == "cyan_950") return color_cyan_950;

            if (col == "sky_50") return color_sky_50;
            if (col == "sky_100") return color_sky_100;
            if (col == "sky_200") return color_sky_200;
            if (col == "sky_300") return color_sky_300;
            if (col == "sky_400") return color_sky_400;
            if (col == "sky_500") return color_sky_500;
            if (col == "sky_600") return color_sky_600;
            if (col == "sky_700") return color_sky_700;
            if (col == "sky_800") return color_sky_800;
            if (col == "sky_900") return color_sky_900;
            if (col == "sky_950") return color_sky_950;

            if (col == "blue_50") return color_blue_50;
            if (col == "blue_100") return color_blue_100;
            if (col == "blue_200") return color_blue_200;
            if (col == "blue_300") return color_blue_300;
            if (col == "blue_400") return color_blue_400;
            if (col == "blue_500") return color_blue_500;
            if (col == "blue_600") return color_blue_600;
            if (col == "blue_700") return color_blue_700;
            if (col == "blue_800") return color_blue_800;
            if (col == "blue_900") return color_blue_900;
            if (col == "blue_950") return color_blue_950;

            if (col == "indigo_50") return color_indigo_50;
            if (col == "indigo_100") return color_indigo_100;
            if (col == "indigo_200") return color_indigo_200;
            if (col == "indigo_300") return color_indigo_300;
            if (col == "indigo_400") return color_indigo_400;
            if (col == "indigo_500") return color_indigo_500;
            if (col == "indigo_600") return color_indigo_600;
            if (col == "indigo_700") return color_indigo_700;
            if (col == "indigo_800") return color_indigo_800;
            if (col == "indigo_900") return color_indigo_900;
            if (col == "indigo_950") return color_indigo_950;

            if (col == "violet_50") return color_violet_50;
            if (col == "violet_100") return color_violet_100;
            if (col == "violet_200") return color_violet_200;
            if (col == "violet_300") return color_violet_300;
            if (col == "violet_400") return color_violet_400;
            if (col == "violet_500") return color_violet_500;
            if (col == "violet_600") return color_violet_600;
            if (col == "violet_700") return color_violet_700;
            if (col == "violet_800") return color_violet_800;
            if (col == "violet_900") return color_violet_900;
            if (col == "violet_950") return color_violet_950;

            if (col == "purple_50") return color_purple_50;
            if (col == "purple_100") return color_purple_100;
            if (col == "purple_200") return color_purple_200;
            if (col == "purple_300") return color_purple_300;
            if (col == "purple_400") return color_purple_400;
            if (col == "purple_500") return color_purple_500;
            if (col == "purple_600") return color_purple_600;
            if (col == "purple_700") return color_purple_700;
            if (col == "purple_800") return color_purple_800;
            if (col == "purple_900") return color_purple_900;
            if (col == "purple_950") return color_purple_950;

            if (col == "fuchsia_50") return color_fuchsia_50;
            if (col == "fuchsia_100") return color_fuchsia_100;
            if (col == "fuchsia_200") return color_fuchsia_200;
            if (col == "fuchsia_300") return color_fuchsia_300;
            if (col == "fuchsia_400") return color_fuchsia_400;
            if (col == "fuchsia_500") return color_fuchsia_500;
            if (col == "fuchsia_600") return color_fuchsia_600;
            if (col == "fuchsia_700") return color_fuchsia_700;
            if (col == "fuchsia_800") return color_fuchsia_800;
            if (col == "fuchsia_900") return color_fuchsia_900;
            if (col == "fuchsia_950") return color_fuchsia_950;

            if (col == "pink_50") return color_pink_50;
            if (col == "pink_100") return color_pink_100;
            if (col == "pink_200") return color_pink_200;
            if (col == "pink_300") return color_pink_300;
            if (col == "pink_400") return color_pink_400;
            if (col == "pink_500") return color_pink_500;
            if (col == "pink_600") return color_pink_600;
            if (col == "pink_700") return color_pink_700;
            if (col == "pink_800") return color_pink_800;
            if (col == "pink_900") return color_pink_900;
            if (col == "pink_950") return color_pink_950;

            if (col == "rose_50") return color_rose_50;
            if (col == "rose_100") return color_rose_100;
            if (col == "rose_200") return color_rose_200;
            if (col == "rose_300") return color_rose_300;
            if (col == "rose_400") return color_rose_400;
            if (col == "rose_500") return color_rose_500;
            if (col == "rose_600") return color_rose_600;
            if (col == "rose_700") return color_rose_700;
            if (col == "rose_800") return color_rose_800;
            if (col == "rose_900") return color_rose_900;
            if (col == "rose_950") return color_rose_950;

            if (col == "slate_50") return color_slate_50;
            if (col == "slate_100") return color_slate_100;
            if (col == "slate_200") return color_slate_200;
            if (col == "slate_300") return color_slate_300;
            if (col == "slate_400") return color_slate_400;
            if (col == "slate_500") return color_slate_500;
            if (col == "slate_600") return color_slate_600;
            if (col == "slate_700") return color_slate_700;
            if (col == "slate_800") return color_slate_800;
            if (col == "slate_900") return color_slate_900;
            if (col == "slate_950") return color_slate_950;

            if (col == "gray_50") return color_gray_50;
            if (col == "gray_100") return color_gray_100;
            if (col == "gray_200") return color_gray_200;
            if (col == "gray_300") return color_gray_300;
            if (col == "gray_400") return color_gray_400;
            if (col == "gray_500") return color_gray_500;
            if (col == "gray_600") return color_gray_600;
            if (col == "gray_700") return color_gray_700;
            if (col == "gray_800") return color_gray_800;
            if (col == "gray_900") return color_gray_900;
            if (col == "gray_950") return color_gray_950;

            if (col == "zinc_50") return color_zinc_50;
            if (col == "zinc_100") return color_zinc_100;
            if (col == "zinc_200") return color_zinc_200;
            if (col == "zinc_300") return color_zinc_300;
            if (col == "zinc_400") return color_zinc_400;
            if (col == "zinc_500") return color_zinc_500;
            if (col == "zinc_600") return color_zinc_600;
            if (col == "zinc_700") return color_zinc_700;
            if (col == "zinc_800") return color_zinc_800;
            if (col == "zinc_900") return color_zinc_900;
            if (col == "zinc_950") return color_zinc_950;

            if (col == "neutral_50") return color_neutral_50;
            if (col == "neutral_100") return color_neutral_100;
            if (col == "neutral_200") return color_neutral_200;
            if (col == "neutral_300") return color_neutral_300;
            if (col == "neutral_400") return color_neutral_400;
            if (col == "neutral_500") return color_neutral_500;
            if (col == "neutral_600") return color_neutral_600;
            if (col == "neutral_700") return color_neutral_700;
            if (col == "neutral_800") return color_neutral_800;
            if (col == "neutral_900") return color_neutral_900;
            if (col == "neutral_950") return color_neutral_950;

            if (col == "stone_50") return color_stone_50;
            if (col == "stone_100") return color_stone_100;
            if (col == "stone_200") return color_stone_200;
            if (col == "stone_300") return color_stone_300;
            if (col == "stone_400") return color_stone_400;
            if (col == "stone_500") return color_stone_500;
            if (col == "stone_600") return color_stone_600;
            if (col == "stone_700") return color_stone_700;
            if (col == "stone_800") return color_stone_800;
            if (col == "stone_900") return color_stone_900;
            if (col == "stone_950") return color_stone_950;

            if (col == "black") return color_black;
            if (col == "white") return color_white;
            if (col == "transparent") return color_transparent;

            return color_transparent;
        }
    };
}