#include "cache.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <unordered_map>

namespace ImModernUI {
    static std::unordered_map<std::string, nlohmann::json> ui_cache;
    bool CacheSet(
        const std::string& key, 
        const nlohmann::json& val
    ) {
        ui_cache[key] = val;
        return true;
    }

    const nlohmann::json CacheGet(const std::string& key) {
        if (!ui_cache.contains(key)) return nlohmann::json(nullptr);
        return ui_cache[key];
    }
}