#include "ImModernUI.h"

#include "accordion.h"
#include "alert.h"
#include "alertdialog.h"
#include "aspect-ratio.h"
#include "avatar.h"
#include "badge.h"
#include "breadcrumb.h"
#include "button.h"
#include "button-group.h"
#include "calendar.h"
#include "card.h"
#include "carousel.h"
#include "collapsible.h"
#include "combobox.h"
#include "command.h"
#include "dropdownmenu.h"
#include "input-group.h"
#include "input.h"
#include "item.h"
#include "label.h"
#include "lucide.h"
#include "menubar.h"
#include "nfd.h"
#include "nlohmann/json.hpp"
#include "popover.h"
#include "progress.h"
#include "scrollarea.h"
#include "select.h"
#include "separator.h"
#include "slider.h"
#include "sonner.h"
#include "spinner.h"
#include "switch.h"
#include "tabs.h"
#include "textarea.h"
#include "toggle-group.h"
#include "toggle.h"
#include "tooltip.h"
#include "fonts.h"
#include "global.h"
#include "imgui.h"
#include "radio-group.h"
#include "checkbox.h"
#include "themes.h"
#include <format>
#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace ImModernUI {
    void Init(float font_size, UIThemeScheme scheme /* = UIThemeScheme::Light */, 
        UIThemeBaseColor base_color /* = UIThemeBaseColor::Netrual */) {
        UISizes::set_base_font_size(font_size);
        UIThemes::set_theme(scheme, base_color);
        UIFont::load_fonts();

        if (NFD_Init() != NFD_OKAY) 
            std::cout << std::format("NFD Init error: {}", NFD_GetError());
    }

    void UnInit() {
        NFD_Quit();
    }

    void ShowImModernUIDemo(bool& open) {
        ImGui::PushFont(UIFont::font_regular_base());

        std::vector<std::tuple<ImGuiCol, ImVec4>> style_colors {
            {ImGuiCol_WindowBg, UIThemes::background()}, 
            {ImGuiCol_Text, UIThemes::foreground()},
            {ImGuiCol_TitleBg, UIThemes::border()}, 
            {ImGuiCol_TitleBgActive, UIThemes::border()},
            {ImGuiCol_TitleBgCollapsed, UIThemes::border()}, 
            {ImGuiCol_ChildBg, UIThemes::background()}, 
        };
        for (auto& [idx, col]: style_colors) {
            ImGui::PushStyleColor(idx, col);
        }

        std::vector<std::tuple<ImGuiStyleVar, ImVec2>> style_vars_1 {
            {ImGuiStyleVar_WindowPadding, ImVec2(UISizes::p_1(), UISizes::p_1())}, 
            {ImGuiStyleVar_FramePadding, ImVec2(UISizes::p_1(), UISizes::p_1())}, 
        };
        for (const auto& [idx, var]: style_vars_1) {
            ImGui::PushStyleVar(idx, var);
        }

        auto main_viewpoint = ImGui::GetMainViewport();
        auto pos = main_viewpoint->WorkPos;
        auto size = main_viewpoint->WorkSize;

        ImGui::SetNextWindowPos(
            ImVec2(pos.x + size.x - UISizes::basis_2xl(), pos.y), 
            ImGuiCond_FirstUseEver
        );
        ImGui::SetNextWindowSize(ImVec2(UISizes::basis_2xl(), 0));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
        if (ImGui::Begin("ImModernUI Demo Window", &open, flags)) {
            std::vector<std::tuple<std::string, std::function<void()>>> ui_demos = {
                {"Accordion", []() { ShowAccordionExamples(); }},
                {"Alert Dialog", []() { ShowAlertDialogExamples(); }},
                {"Alert", []() { ShowAlertExamples(); }},
                {"Aspect Ratio", []() { ShowAspectRatioExamples(); }},
                {"Avatar", []() { ShowAvatarExamples(); }},
                {"Badge", []() { ShowBadgeExamples(); }},
                {"Breadcrumb", []() { ShowBreadcrumbExamples(); }},
                {"Button Group", []() { ShowButtonGroupExamples(); }},
                {"Button", []() { ShowButtonExamples(); }},
                {"Calendar", []() { ShowCalendarExamples(); }},
                {"Card", []() { ShowCardExamples(); }},
                {"Carousel", []() { ShowCarouselExamples(); }},
                {"Chart", []() {}},
                {"Checkbox", []() { ShowCheckboxExamples(); }},
                {"Collapsible", []() { ShowCollapsibleExamples(); }},
                {"Combobox", []() { ShowComboboxExamples(); }},
                {"Command", []() { ShowCommandExamples(); }},
                {"Context Menu", []() {}},
                {"Data Table", []() {}},
                {"Date Picker", []() {}},
                {"Dialog", []() {}},
                {"Drawer", []() {}},
                {"Dropdown Menu", []() { ShowDropdownMenuExamples(); }},
                {"Field", []() {}},
                {"Form", []() {}},
                {"Hover Card", []() {}},
                {"Input Group", []() { ShowInputGroupExamples(); }},
                {"Input", []() { ShowInputExamples(); }},
                {"Item", []() { ShowItemExamples(); }},
                {"Label", []() { ShowLabelExamples(); }},
                {"Menubar", []() { ShowMenubarExamples(); }},
                {"Native Select", []() {}},
                {"Navigation Menu", []() {}},
                {"Pagination", []() {}},
                {"Popover", []() { ShowPopoverExamples(); }},
                {"Progress", []() { ShowProgressExamples(); }},
                {"Radio Group", []() { ShowRadioGroupExamples(); }},
                {"Resizable", []() {}},
                {"Scroll Area", []() { ShowScrollAreaExamples(); }},
                {"Select", []() { ShowSelectExamples(); }},
                {"Separator", []() { ShowSeparatorExamples(); }},
                {"Sheet", []() {}},
                {"Sidebar", []() {}},
                {"Skeleton", []() {}},
                {"Slider", []() { ShowSliderExamples(); }},
                {"Sonner", []() { ShowSonnerExamples(); }},
                {"Spinner", []() { ShowSpinnerExamples(); }},
                {"Switch", []() { ShowSwitchExamples(); }},
                {"Table", []() {}},
                {"Tabs", []() { ShowTabsExamples(); }},
                {"Textarea", []() { ShowTextareaExamples(); }},
                {"Toggle Group", []() { ShowToggleGroupExamples(); }},
                {"Toggle", []() { ShowToggleExamples(); }},
                {"Tooltip", []() { ShowTooltipExamples(); }},
                {"Typography", []() {}},
            };

            static std::unordered_map<std::string, bool> state;
            for (auto [key, func]: ui_demos) {
                bool item_open = false;
                if (state.contains(key)) item_open = state[key];
                item_open = ImModernUI::Collapsible(
                    key, 
                    [](const std::string& label, bool open) {
                        nlohmann::json attr;
                        attr["label"] = label;
                        attr["variant"] = "ghost";
                        attr["size"] = "full-sm";
                        attr["icon"] = (open ? ICON_CHEVRON_DOWN : ICON_CHEVRON_RIGHT);
                        attr["icon-align"] = "right";
                        return ImModernUI::Button(attr);
                    }, 
                    [&](const std::string& label) {
                        float x = ImGui::GetContentRegionAvail().x;
                        float scale = 0.6;
                        if (label == "Calendar") scale = 0.95;
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + x * (1.0 - scale) * 0.5);
                        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
                        if (ImGui::BeginChild(
                                std::format("##ImModernUI Examples: {}", key).c_str(), 
                                ImVec2(x * scale, 0), 
                                flags
                        )) {
                            func();
                        }
                        ImGui::EndChild();
                    }, 
                    item_open
                );
                state[key] = item_open;
            }
        }
        ImGui::End();

        ImGui::PopStyleVar(style_vars_1.size());
        ImGui::PopStyleColor(style_colors.size());
        ImGui::PopFont();
    }
}