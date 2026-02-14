#pragma once

#include "nlohmann/json_fwd.hpp"

namespace ImModernUI {
    struct UIState {
        static void PushState(const nlohmann::json& state);
        static void PopState();
        static const nlohmann::json& PeekState();
    };
}
