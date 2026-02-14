#include "menubar.h"

#include "imgui.h"
#include "nlohmann/json.hpp"

namespace ImModernUI {
    bool Menubar(
        const nlohmann::json& attr, 
        std::function<void(const std::string& label)> handler
    ) {
        return true;
    }

    void ShowMenubarExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild(
            "##Menubar Examples", 
            ImVec2(0, 0), 
            flags
        );

        {
            static nlohmann::json attr;

            attr["label"] = "##Menubar example";
            attr["menus"][0]["trigger"] = "File";
            attr["menus"][0]["content"][0]["type"] = "item";
            attr["menus"][0]["content"][0]["text"] = "New Tab";
            attr["menus"][0]["content"][0]["shortcut"] = "⌘T";
            attr["menus"][0]["content"][1]["type"] = "item";
            attr["menus"][0]["content"][1]["text"] = "New Window";
            attr["menus"][0]["content"][1]["shortcut"] = "⌘N";
            attr["menus"][0]["content"][2]["type"] = "item";
            attr["menus"][0]["content"][2]["text"] = "New Incognito Window";
            attr["menus"][0]["content"][2]["disabled"] = true;
            attr["menus"][0]["content"][3]["type"] = "separator";
            attr["menus"][0]["content"][4]["type"] = "submenu";
            attr["menus"][0]["content"][4]["submenu"]["trigger"] = "Share";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][0]["type"] = "item";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][0]["text"] = "Email link";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][1]["type"] = "item";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][1]["text"] = "Messages";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][2]["type"] = "item";
            attr["menus"][0]["content"][4]["submenu"]["subcontent"][2]["text"] = "Notes";
            attr["menus"][0]["content"][5]["type"] = "item";
            attr["menus"][0]["content"][5]["text"] = "Print...";
            attr["menus"][0]["content"][5]["shortcut"] = "⌘P";

            attr["menus"][1]["trigger"] = "Edit";
            attr["menus"][1]["content"][0]["type"] = "item";
            attr["menus"][1]["content"][0]["text"] = "Undo";
            attr["menus"][1]["content"][0]["shortcut"] = "⌘Z";
            attr["menus"][1]["content"][1]["type"] = "item";
            attr["menus"][1]["content"][1]["text"] = "Redo";
            attr["menus"][1]["content"][1]["shortcut"] = "⇧⌘Z";
            attr["menus"][1]["content"][3]["type"] = "separator";
            attr["menus"][1]["content"][4]["type"] = "submenu";
            attr["menus"][1]["content"][4]["submenu"]["trigger"] = "Find";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][0]["type"] = "item";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][0]["text"] = "Search the web";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][1]["type"] = "separator";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][2]["type"] = "item";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][2]["text"] = "Find...";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][3]["type"] = "item";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][3]["text"] = "Find Next";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][4]["type"] = "item";
            attr["menus"][1]["content"][4]["submenu"]["subcontent"][4]["text"] = "Find Previous";
            attr["menus"][1]["content"][5]["type"] = "separator";
            attr["menus"][1]["content"][6]["type"] = "item";
            attr["menus"][1]["content"][6]["text"] = "Cut";
            attr["menus"][1]["content"][7]["type"] = "item";
            attr["menus"][1]["content"][7]["text"] = "Copy";
            attr["menus"][1]["content"][8]["type"] = "item";
            attr["menus"][1]["content"][8]["text"] = "Paste";

            attr["menus"][2]["trigger"] = "View";
            attr["menus"][2]["content"][0]["type"] = "checkbox";
            attr["menus"][2]["content"][0]["text"] = "Always Show Bookmarks Bar";
            attr["menus"][2]["content"][0]["checked"] = false;
            attr["menus"][2]["content"][1]["type"] = "checkbox";
            attr["menus"][2]["content"][1]["text"] = "Always Show Full URLs";
            attr["menus"][2]["content"][1]["checked"] = true;
            attr["menus"][2]["content"][2]["type"] = "separator";
            attr["menus"][2]["content"][3]["type"] = "item";
            attr["menus"][2]["content"][3]["text"] = "Reload";
            attr["menus"][2]["content"][3]["shortcut"] = "⌘R";
            attr["menus"][2]["content"][4]["type"] = "item";
            attr["menus"][2]["content"][4]["text"] = "Force Reload";
            attr["menus"][2]["content"][4]["shortcut"] = "⇧⌘R";
            attr["menus"][2]["content"][4]["disabled"] = true;
            attr["menus"][2]["content"][5]["type"] = "separator";
            attr["menus"][2]["content"][6]["type"] = "item";
            attr["menus"][2]["content"][6]["text"] = "Toggle Fullscreen";
            attr["menus"][2]["content"][7]["type"] = "separator";
            attr["menus"][2]["content"][8]["type"] = "item";
            attr["menus"][2]["content"][8]["text"] = "Hide Sidebar";

            attr["menus"][3]["trigger"] = "Profiles";
            attr["menus"][3]["content"][0]["type"] = "ratiogroup";
            attr["menus"][3]["content"][0]["value"] = "benoit";
            attr["menus"][3]["content"][0]["items"][0]["label"] = "Andy";
            attr["menus"][3]["content"][0]["items"][0]["value"] = "andy";
            attr["menus"][3]["content"][0]["items"][1]["label"] = "Benoit";
            attr["menus"][3]["content"][0]["items"][1]["value"] = "benoit";
            attr["menus"][3]["content"][0]["items"][2]["label"] = "Luis";
            attr["menus"][3]["content"][0]["items"][2]["value"] = "luis";
            attr["menus"][3]["content"][1]["type"] = "separator";
            attr["menus"][3]["content"][2]["type"] = "item";
            attr["menus"][3]["content"][2]["text"] = "Edit...";
            attr["menus"][3]["content"][3]["type"] = "separator";
            attr["menus"][3]["content"][4]["type"] = "item";
            attr["menus"][3]["content"][4]["text"] = "Add Profile...";
        }

        ImGui::EndChild();
    }
}