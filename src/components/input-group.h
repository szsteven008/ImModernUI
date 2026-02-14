#pragma once

#include "imgui.h"
#include <functional>
#include <string>

namespace ImModernUI {
    bool InputGroup(
        const std::string& label, 
        const std::string& placeholder, 
        char * buf, 
        int buf_size, 
        bool border = true, 
        bool readonly = false, 
        ImVec2 size_arg = ImVec2(0, 0), 
        const std::string align = "inline", // inline|block
        std::function<void(float, char *, int)> prefix = nullptr, 
        std::function<void(float, char *, int)> suffix = nullptr
    );

    void ShowInputGroupExamples();
}