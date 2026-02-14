#include "collapsible.h"

#include "button.h"
#include "card.h"
#include "fonts.h"
#include "global.h"
#include "group.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "input.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "tabs.h"
#include "themes.h"
#include <array>
#include <format>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace ImModernUI {

    bool Collapsible(
        const std::string& label, 
        std::function<bool(const std::string&, bool)> trigger, 
        std::function<void(const std::string&)> content, 
        bool open
    ) {
        static std::unordered_map<ImGuiID, bool> collapsible_state;
        auto id = ImGui::GetID(label.c_str());
        ImGui::PushID(id);

        ImModernUI::BeginGroup();
        if (trigger(label, open)) open = !open;
        if (open && content) {
            content(label);
        }
        ImModernUI::EndGroup();

        ImGui::PopID();

        return open;
    }

    void ShowCollapsibleExamples() {
        ImGui::SeparatorText("Usage");
        {
            static bool open = false;
            open = Collapsible(
                "##Collapsible Examples: Usage", 
                [](const std::string& label, bool open) {
                    float width = 320;
                    bool pressed = false;
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 
                        UISizes::rounded_md());
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
                        ImVec2(UISizes::p_4(), 0));
                    ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
                    flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
                    if (ImGui::BeginChild(
                        std::format("{}.trigger", label).c_str(), 
                        ImVec2(width, 0), 
                        flags
                    )) {
                        auto pos = ImGui::GetCursorPos();
                        auto x = ImGui::GetContentRegionAvail().x;
                        ImGui::SetCursorPosY(
                            pos.y + 
                                (UISizes::size_8() - UISizes::text_sm()) * 0.5
                        );
                        ImGui::PushFont(UIFont::font_medium_sm());
                        ImGui::TextUnformatted("Order #4189");
                        ImGui::PopFont();

                        ImGui::SetCursorPos(
                            ImVec2(
                                pos.x + x - UISizes::size_8(), 
                                pos.y
                            )
                        );

                        nlohmann::json attr;
                        attr["label"] = "##collapsible trigger";
                        attr["variant"] = "ghost";
                        attr["size"] = "icon-sm";
                        attr["icon"] = ICON_CHEVRONS_UP_DOWN;
                        pressed = ImModernUI::Button(attr);
                    }
                    ImGui::EndChild();
                    ImGui::PopStyleVar();

                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
                        ImVec2(UISizes::p_4(), UISizes::p_2()));

                    flags |= ImGuiChildFlags_Borders;
                    if (ImGui::BeginChild(
                        std::format("{}.description", label).c_str(), 
                        ImVec2(width, 0), 
                        flags
                    )) {
                        auto pos = ImGui::GetCursorPos();
                        auto x = ImGui::GetContentRegionAvail().x;

                        ImGui::PushFont(UIFont::font_regular_sm());
                        ImGui::PushStyleColor(ImGuiCol_Text, 
                            UIThemes::muted_foreground());
                        ImGui::TextUnformatted("Status");
                        ImGui::PopStyleColor();
                        ImGui::PopFont();

                        ImGui::PushFont(UIFont::font_medium_sm());
                        auto text_size = ImGui::CalcTextSize("Shipped");
                        ImGui::SetCursorPos(
                            ImVec2(
                                pos.x + x - text_size.x, 
                                pos.y
                            )
                        );
                        ImGui::TextUnformatted("Shipped");
                        ImGui::PopFont();
                    }
                    ImGui::EndChild();

                    ImGui::PopStyleVar(2);

                    return pressed;
                }, 
                [](const std::string& label) {
                    std::vector<std::array<std::string, 2>> data {
                        {"Shipping address", "100 Market St, San Francisco"},
                        {"Items", "2x Studio Headphones"},
                    };

                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, 
                        ImVec2(UISizes::p_4(), UISizes::p_2()));
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 
                        UISizes::rounded_md());
                    for (int i=0; i<data.size(); ++i) {
                        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
                        flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
                        flags |= ImGuiChildFlags_Borders;
                        if (ImGui::BeginChild(
                            std::format("{}.content.{}", label, i).c_str(), 
                            ImVec2(320, 0), 
                            flags
                        )) {
                            ImGui::PushFont(UIFont::font_medium_sm());
                            ImGui::TextUnformatted(data[i][0].c_str());
                            ImGui::PopFont();

                            ImGui::PushFont(UIFont::font_regular_sm());
                            ImGui::PushStyleColor(ImGuiCol_Text, 
                                UIThemes::muted_foreground());
                            ImGui::TextUnformatted(data[i][1].c_str());
                            ImGui::PopStyleColor();
                            ImGui::PopFont();
                        }
                        ImGui::EndChild();
                    }
                    ImGui::PopStyleVar(2);
                }, 
                open
            );
        }
        ImGui::SeparatorText("Basic");
        {
            static nlohmann::json data;
            nlohmann::json attr;
            attr["label"] = "##Collapsible Examples: Basic";
            Card(
                attr, 
                ImVec2(320, 0), 
                data, 
                nullptr, 
                [](nlohmann::json& data) {
                    bool open = false;
                    if (data.contains("open"))
                        open = data["open"].get<bool>();

                    ImDrawListSplitter dls;
                    auto dl = ImGui::GetWindowDrawList();
                    dls.Split(dl, 2);
                    dls.SetCurrentChannel(dl, 1);
                    open = Collapsible(
                        "##Collapsible Examples - Basic", 
                        [](const std::string& label, bool open) {
                            nlohmann::json trigger;
                            trigger["label"] = std::format("Product details##{}.trigger", label);
                            trigger["variant"] = "ghost";
                            trigger["size"] = "full";
                            trigger["icon"] = (open ? ICON_CHEVRON_UP : ICON_CHEVRON_DOWN);
                            trigger["icon-align"] = "right";
                            return ImModernUI::Button(trigger);
                        }, 
                        [](const std::string& label) {
                            ImGui::Indent(UISizes::p_4());
                            ImGui::PushFont(UIFont::font_regular_sm());
                            auto x = ImGui::GetContentRegionAvail().x;
                            ImGui::PushTextWrapPos(
                                ImGui::GetCursorPosX() + x
                            );
                            ImGui::TextUnformatted("This panel can be expanded or "
                                "collapsed to reveal additionalcontent.");
                            ImGui::PopTextWrapPos();
                            ImGui::PopFont();

                            nlohmann::json attr;
                            attr["label"] = std::format("Learn More##{}", label);
                            attr["variant"] = "primary";
                            attr["size"] = "xs";
                            ImModernUI::Button(attr);

                            ImGui::Dummy(ImVec2(0, UISizes::p_2()));
                        }, 
                        open
                    );

                    data["open"] = open;
                    if (open) {
                        auto min = ImGui::GetItemRectMin();
                        auto max = ImGui::GetItemRectMax();
                        dls.SetCurrentChannel(dl, 0);
                        dl->AddRectFilled(
                            min, 
                            max, 
                            ImGui::GetColorU32(UIThemes::muted()), 
                            UISizes::rounded_md()
                        );
                    }
                    dls.Merge(dl);
                }
            );
        }
        ImGui::SeparatorText("Settings Panel");
        {
            static nlohmann::json data;
            nlohmann::json attr;
            attr["label"] = "##Collapsible Examples: Settings Panel.Card";
            attr["title"] = "Radius";
            attr["description"] = "Set the corner radius of the element.";
            Card(
                attr, 
                ImVec2(320, 0), 
                data, 
                nullptr, 
                [](nlohmann::json& data) {
                    bool open = false;
                    if (data.contains("open")) 
                        open = data["open"].get<bool>();
                    open = Collapsible(
                        "##Collapsible Examples: Settings Panel.Collapsible", 
                        [](const std::string& label, bool open) {
                            int width = ImGui::GetContentRegionAvail().x;
                            width -= UISizes::w_9() + UISizes::m_2() * 2;
                            width *= 0.5;

                            static char buf[2][1024];
                            for (int i=0; i<2; ++i) {
                                if (i > 0) ImGui::SameLine();
                                nlohmann::json attr;
                                attr["label"] = std::format("{}.input.{}", label, i);
                                attr["placeholder"] = "0";
                                Input(
                                    attr, 
                                    ImVec2(width, 0), 
                                    buf[i], 
                                    sizeof(buf[i])
                                );
                            }

                            ImGui::SameLine();
                            nlohmann::json attr;
                            attr["label"] = std::format("{}.trigger", label);
                            attr["variant"] = "outline";
                            attr["size"] = "icon";
                            attr["icon"] = open ? ICON_MINIMIZE : ICON_MAXIMIZE;
                            return ImModernUI::Button(attr);
                        }, 
                        [](const std::string& label) {
                            int width = ImGui::GetContentRegionAvail().x;
                            width -= UISizes::w_9() + UISizes::m_2() * 2;
                            width *= 0.5;

                            static char buf[2][1024];
                            for (int i=0; i<2; ++i) {
                                if (i > 0) ImGui::SameLine();
                                nlohmann::json attr;
                                attr["label"] = std::format("{}.input.{}", label, i + 2);
                                attr["type"] = "text";
                                attr["placeholder"] = "0";
                                Input(
                                    attr, 
                                    ImVec2(width, 0), 
                                    buf[i], 
                                    sizeof(buf[i])
                                );
                            }
                        }, 
                        open
                    );
                    data["open"] = open;
                }
            );
        }
        ImGui::SeparatorText("File Tree");
        {
            nlohmann::json attr;
            attr["label"] = "##Collapsible Examples: File Tree";
            nlohmann::json data = nlohmann::json::value_t::null;
            Card(
                attr, 
                ImVec2(256, 0), 
                data, 
                nullptr, 
                [](nlohmann::json& data) {
                    static int tab_selected = 0;
                    float max_width = ImGui::GetContentRegionAvail().x;
                    nlohmann::json attr;
                    attr["label"] = "##Collapsible Examples: File Tree: Tab";
                    attr["align"] = "center";
                    attr["items"] = R"(
                        [
                            {"name": "Explorer"}, 
                            {"name": "Outline"}
                        ]
                    )"_json;
                    ImModernUI::Tabs(
                        attr, &
                        tab_selected, 
                        [](int index) {
                            static std::vector<std::string> file_items {
                                "components/", 
                                "lib/", 
                                "hooks/", 
                                "types/", 
                                "public/", 
                                "app.tsx", 
                                "layout.tsx", 
                                "globals.css", 
                                "package.json", 
                                "tsconfig.json", 
                                "README.md", 
                                ".gitignore", 
                            };
                            static std::unordered_map<std::string, std::vector<std::string>> file_subitems {
                                {
                                    "components/", 
                                    {
                                        "components/ui/", 
                                        "components/login-form.tsx", 
                                        "components/register-form.tsx"
                                    }
                                }, 
                                {
                                    "components/ui/", 
                                    {
                                        "components/ui/button.tsx", 
                                        "components/ui/card.tsx", 
                                        "components/ui/dialog.tsx", 
                                        "components/ui/input.tsx", 
                                        "components/ui/select.tsx", 
                                        "components/ui/table.tsx", 
                                    }
                                }, 
                                {
                                    "lib/", 
                                    {
                                        "lib/utils.ts", 
                                        "lib/cn.ts", 
                                        "lib/api.ts",                                         
                                    }
                                }, 
                                {
                                    "hooks/", 
                                    {
                                        "hooks/use-media-query.ts", 
                                        "hooks/use-debounce.ts", 
                                        "hooks/use-local-storage.ts", 
                                    }
                                }, 
                                {
                                    "types/", 
                                    {
                                        "types/index.d.ts", 
                                        "types/api.d.ts", 
                                    }
                                }, 
                                {
                                    "public/", 
                                    {
                                        "public/favicon.ico", 
                                        "public/logo.svg", 
                                        "public/images", 
                                    }
                                }
                            };

                            auto render_file = [](
                                const std::string& name, 
                                float offset
                            ) {
                                auto id = ImGui::GetID(name.c_str());

                                float width = ImGui::GetContentRegionAvail().x - offset;
                                float height = UISizes::h_6();
                                auto pos = ImGui::GetCursorScreenPos();
                                ImRect bb {
                                    pos.x + offset, 
                                    pos.y, 
                                    pos.x + width, 
                                    pos.y + height
                                };
                                ImGui::ItemSize(bb.GetSize());
                                ImGui::ItemAdd(bb, id);

                                bool hovered = false;
                                bool pressed = ImGui::ButtonBehavior(
                                    bb, 
                                    id, 
                                    &hovered, 
                                    nullptr
                                );

                                auto draw = ImGui::GetWindowDrawList();
                                float x = bb.Min.x + UISizes::p_4();
                                ImGui::PushFont(UIFont::font_icon());
                                draw->AddText(
                                    ImVec2(
                                        x, 
                                        (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5
                                    ), 
                                    ImGui::GetColorU32(UIThemes::foreground()), 
                                    ICON_FILE
                                );
                                x += UISizes::size_4() + UISizes::m_2();
                                ImGui::PopFont();

                                auto size = ImGui::CalcTextSize(name.c_str());
                                draw->AddText(
                                    ImVec2(
                                        x, 
                                        (bb.Min.y + bb.Max.y - size.y) * 0.5
                                    ), 
                                    ImGui::GetColorU32(UIThemes::foreground()), 
                                    name.c_str()
                                );
                                if (hovered) {
                                    draw->AddLine(
                                        ImVec2(
                                            x, 
                                            (bb.Min.y + bb.Max.y + size.y) * 0.5
                                        ), 
                                        ImVec2(
                                            x + size.x, 
                                            (bb.Min.y + bb.Max.y + size.y) * 0.5
                                        ), 
                                        ImGui::GetColorU32(UIThemes::foreground())
                                    );
                                }

                                return pressed;
                            };
                            std::function<
                                void(
                                    const std::string&, 
                                    const std::string&, 
                                    const std::vector<std::string>&, 
                                    int, 
                                    float
                                )
                            > render_dir = [&](
                                const std::string& parent, 
                                const std::string& name, 
                                const std::vector<std::string>& items, 
                                int width, 
                                float offset
                            ) {
                                static std::unordered_map<std::string, bool> state;
                                bool open = false;
                                if (state.contains(name)) open = state[name];
                                open = Collapsible(
                                    name, 
                                    [&](const std::string& name, bool open) {                                        
                                        auto id = ImGui::GetID(name.c_str());

                                        float height = UISizes::h_6();
                                        auto pos = ImGui::GetCursorScreenPos();
                                        ImRect bb {
                                            pos.x + offset, 
                                            pos.y, 
                                            pos.x + width, 
                                            pos.y + height
                                        };
                                        ImGui::ItemSize(bb.GetSize());
                                        ImGui::ItemAdd(bb, id);
                                    
                                        bool hovered = false;
                                        bool pressed = ImGui::ButtonBehavior(
                                            bb, 
                                            id, 
                                            &hovered, 
                                            nullptr
                                        );
                                    
                                        auto draw = ImGui::GetWindowDrawList();
                                        if (hovered) {
                                            draw->AddRectFilled(
                                                bb.Min, 
                                                bb.Max, 
                                                ImGui::GetColorU32(UIThemes::accent()), 
                                                UISizes::rounded_md()
                                            );
                                        }
                                    
                                        float x = bb.Min.x + UISizes::p_4();
                                        ImGui::PushFont(UIFont::font_icon());
                                        draw->AddText(
                                            ImVec2(
                                                x, 
                                                (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5
                                            ), 
                                            ImGui::GetColorU32(UIThemes::foreground()), 
                                            open ? ICON_CHEVRON_DOWN : ICON_CHEVRON_RIGHT
                                        );
                                        x += UISizes::size_4() + UISizes::m_2();
                                        draw->AddText(
                                            ImVec2(
                                                x, 
                                                (bb.Min.y + bb.Max.y - UISizes::size_4()) * 0.5
                                            ), 
                                            ImGui::GetColorU32(UIThemes::foreground()), 
                                            ICON_FOLDER
                                        );
                                        x += UISizes::size_4() + UISizes::m_2();
                                        ImGui::PopFont();
                                    
                                        auto size = ImGui::CalcTextSize(name.c_str());
                                        draw->AddText(
                                            ImVec2(
                                                x, 
                                                (bb.Min.y + bb.Max.y - size.y) * 0.5
                                            ), 
                                            ImGui::GetColorU32(
                                                hovered ? UIThemes::accent_foreground() : 
                                                    UIThemes::foreground()
                                            ), 
                                            name.substr(
                                                parent.size(), 
                                                name.size() - parent.size() - 1
                                            ).c_str()
                                        );
                                    
                                        return pressed;
                                    }, 
                                    [&](const std::string& name) {
                                        for (const auto& item: items) {
                                            if (item.ends_with('/')) {
                                                render_dir(
                                                    name, 
                                                    item, 
                                                    file_subitems[item], 
                                                    width - offset, 
                                                    offset + UISizes::p_4()
                                                );
                                                continue;
                                            }

                                            render_file(
                                                item.substr(name.size()), 
                                                offset + UISizes::p_4()
                                            );
                                        }
                                    }, 
                                    open
                                );
                                state[name] = open;
                            };

                            ImModernUI::BeginGroup();
                            for (const auto& item: file_items) {
                                if (item.ends_with('/')) {
                                    render_dir(
                                        "", 
                                        item, 
                                        file_subitems[item], 
                                        ImGui::GetContentRegionAvail().x, 
                                        0
                                    );
                                    continue;
                                }

                                render_file(item, 0);
                            }
                            ImModernUI::EndGroup();
                        }, 
                        max_width
                    );
                }
            );
        }
    }
}