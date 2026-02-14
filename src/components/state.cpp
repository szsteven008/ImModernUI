#include "state.h"
#include <vector>

#include "nlohmann/json.hpp"

namespace ImModernUI {
    static std::vector<nlohmann::json> state_stack;

    void UIState::PushState(const nlohmann::json& state) {
        state_stack.push_back(state);
    }

    void UIState::PopState() {
        state_stack.pop_back();
    }

    const nlohmann::json& UIState::PeekState() {
        return state_stack.back();
    }
}