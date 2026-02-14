#include "combobox.h"

#include "imgui.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <string>
#include <vector>

namespace ImModernUI {
    static bool default_trigger(
        const std::string& label, 
        const std::string& placeholder, 
        const ImVec2& size_arg, 
        char * buf, 
        int buf_size
    ) {
        bool changed = false;
        return changed;
    }

    bool Combobox(
        const nlohmann::json& attr, 
        std::vector<std::string>& value
    ) {
        if (!attr.contains("label") || 
            (!attr.contains("items") && 
            !attr.contains("groups"))) return false;
        std::string placeholder = "";
        if (attr.contains("placeholder")) 
            placeholder = attr["placeholder"].get<std::string>();

        
        
        if (attr.contains("groups")) {
            std::vector<nlohmann::json> groups = 
                attr["groups"].get<std::vector<nlohmann::json>>();
        } else {
            std::vector<std::string> items = 
                attr["items"].get<std::vector<std::string>>();
        }

        return true;
    }

    void ShowComboboxExamples() {
        ImGui::SeparatorText("Basic");
        {
            static std::vector<std::string> value;
            nlohmann::json attr = R"(
                {
                    "label": "Basic", 
                    "placeholder": "Select a framework", 
                    "items": [
                        "Next.js",
                        "SvelteKit",
                        "Nuxt.js",
                        "Remix",
                        "Astro"
                    ]
                }
            )"_json;

            Combobox(
                attr, 
                value
            );
        }
        ImGui::SeparatorText("Multiple");
        {}
        ImGui::SeparatorText("Clear Button");
        {}
        ImGui::SeparatorText("Groups");
        {}
        ImGui::SeparatorText("Custom Items");
        {}
        ImGui::SeparatorText("Invalid");
        {}
        ImGui::SeparatorText("Disabled");
        {}
        ImGui::SeparatorText("Auto Highlight");
        {}
        ImGui::SeparatorText("Popup");
        {}
        ImGui::SeparatorText("Input Group");
        {}
    }
}