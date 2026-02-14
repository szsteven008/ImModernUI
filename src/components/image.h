#pragma once

#include "imgui.h"
#include <OpenGL/gltypes.h>
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

namespace ImModernUI {
    GLuint load_image(
        const char * path, 
        int * w, 
        int * h, 
        bool grayscale = false
    );

    GLuint load_svg(
        const char * path, 
        int * w, 
        int * h, 
        bool recolor = false, 
        ImVec4 color = ImVec4(0, 0, 0, 0), 
        bool rotate = false, 
        float angle = 0.0
    );
}