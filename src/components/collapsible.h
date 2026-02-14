#pragma once

#include <functional>

namespace ImModernUI {
    bool Collapsible(
        const std::string& label, 
        std::function<bool(const std::string&, bool)> trigger, 
        std::function<void(const std::string&)> content, 
        bool open
    );

    void ShowCollapsibleExamples();
}