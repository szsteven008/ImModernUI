#pragma once

#include "nlohmann/json_fwd.hpp"
#include <string>

namespace ImModernUI {
    bool CacheSet(
        const std::string& key, 
        const nlohmann::json& val
    );
    const nlohmann::json CacheGet(const std::string& key);
}