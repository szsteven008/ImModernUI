#include "sonner.h"

#include "button.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "lucide.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "spinner.h"
#include "themes.h"
#include <ctime>
#include <string>
#include <vector>

namespace ImModernUI {
    std::vector<nlohmann::json> sonners;
    const unsigned long sonner_max_delta = 4;

    bool Sonner(const nlohmann::json& attr) {
        if (!attr.contains("text")) return false;
        nlohmann::json sonner = attr;
        sonner["time"] = time(nullptr);
        sonners.push_back(sonner);
        return true;
    }

    void UpdateSonner() {
        ImGui::PushFont(UIFont::font_medium_sm());
        auto now = time(nullptr);

        float max_width = 0.0f;
        for (auto it = sonners.begin(); 
            it != sonners.end(); 
        ) {
            auto& sonner = *it;
            time_t t = sonner["time"].get<time_t>();
            if ((now - t) >= sonner_max_delta) {
                sonners.erase(it);
                continue;
            }
            ++it;

            std::string text = sonner["text"].get<std::string>();
            float text_width = ImGui::CalcTextSize(
                text.c_str(), 
                ImGui::FindRenderedTextEnd(text.c_str()), 
                true
            ).x;

            if (max_width < text_width) max_width = text_width;
        }

        auto padding = ImVec2(UISizes::p_4(), UISizes::p_4());
        auto gap = ImVec2(UISizes::m_2(), UISizes::m_2());
        max_width += UISizes::size_4() + padding.x * 2 + gap.x;

        auto display_size = ImGui::GetIO().DisplaySize;
        float x = (display_size.x - max_width) * 0.5;
        float y = ImGui::GetStyle().WindowPadding.y;

        for (auto it = sonners.rbegin(); 
            it != sonners.rend(); 
            ++it
        ) {
            auto& sonner = *it;

            std::string icon = "";
            if (sonner.contains("icon")) 
                icon = sonner["icon"].get<std::string>();
            std::string text = sonner["text"].get<std::string>();
            bool promise = false;
            if (sonner.contains("promise")) 
                promise = sonner["promise"].get<bool>();

            float h = padding.y * 2 + UISizes::size_4();

            auto pos = ImVec2(x, y);
            ImRect bb {
                pos.x, 
                pos.y, 
                pos.x + max_width, 
                pos.y + h
            };

            auto draw = ImGui::GetForegroundDrawList();
            draw->AddRectFilled(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(UIThemes::popover()), 
                UISizes::rounded_lg()
            );
            draw->AddRect(
                bb.Min, 
                bb.Max, 
                ImGui::GetColorU32(UIThemes::border()), 
                UISizes::rounded_lg()
            );

            float baseline_x = bb.Min.x + padding.x;
            float baseline_y = (bb.Min.y + bb.Max.y) * 0.5;

            auto col = ImGui::GetColorU32(UIThemes::popover_foreground());
            if (!icon.empty()) {
                if (promise) {
                    ImGui::SetCursorScreenPos(
                        ImVec2(
                            baseline_x, 
                            baseline_y - UISizes::size_4() * 0.5
                        )
                    );
                    ImModernUI::Spinner(text, draw);
                } else {
                    ImGui::PushFont(UIFont::font_icon());
                    draw->AddText(
                        ImVec2(baseline_x, baseline_y - UISizes::size_4() * 0.5), 
                        col, 
                        icon.c_str()
                    );
                    ImGui::PopFont();
                }
                baseline_x += UISizes::size_4();
                baseline_x += gap.x;
            }

            float text_size_y = ImGui::CalcTextSize(text.c_str()).y;
            draw->AddText(
                ImVec2(baseline_x, baseline_y - text_size_y * 0.5), 
                col, 
                text.c_str()
            );            

            y = bb.Max.y + gap.y;
        }

        ImGui::PopFont();
    }

    void ShowSonnerExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Sonner Examples", 
            ImVec2(0, 0), flags);

        std::vector<std::vector<std::string>> examples {
            {"Default", "", "Event has been created"}, 
            {"Success", ICON_CIRCLE_CHECK, "Event has been created"}, 
            {"Info", ICON_INFO, "Be at the area 10 minutes before the event time"}, 
            {"Warning", ICON_TRIANGLE_ALERT, "Event start time cannot be earlier than 8am"}, 
            {"Error", ICON_OCTAGON_X, "Event has not been created"}, 
            {"Promise", ICON_LOADER_CIRCLE, "Loading..."}, 
        };

        for (const auto& e: examples) {
            if (e != examples.front()) ImGui::SameLine();

            nlohmann::json trigger;
            trigger["label"] = e[0];
            trigger["variant"] = "outline";
            if (ImModernUI::Button(trigger)) {
                nlohmann::json attr;
                attr["icon"] = e[1];
                attr["text"] = e[2];
                if (e[0] == "Promise") attr["promise"] = true;
                Sonner(attr);
            }
        }

        UpdateSonner();

        ImGui::EndChild();
    }
}