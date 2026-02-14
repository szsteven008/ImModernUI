#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace ImModernUI {
    bool Calendar(
        const std::string& label, 
        std::vector<std::chrono::year_month_day>& days, /* single: 0 - selected | range: 0-start 1-end */
        bool year_month_selector = false, 
        const std::string size = "default"
    );

    void ShowCalendarExamples();
}