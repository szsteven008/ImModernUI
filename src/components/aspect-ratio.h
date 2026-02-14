#pragma once

#include "nlohmann/json_fwd.hpp"

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

namespace ImModernUI {
    /*
    {
        "label": "##aspect-ratio", 
        "ratio": "16 / 9",
        "rounding": "sm|md|lg|xl", 
        "image": "file name", 
        "texture": texture, 
        "width": width, 
        "height": height, 
        "fit": "contain|cover|fill", 
        "conner": "all|top|bottom|left|right"
    }
    */
    bool AspectRatio(
        const nlohmann::json& attr, 
        float width = 0.0f
    );

    void ShowAspectRatioExamples();
}