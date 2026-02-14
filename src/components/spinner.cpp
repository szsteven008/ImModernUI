#include "spinner.h"

#include "global.h"
#include "image.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace ImModernUI {
    bool Spinner(
        const std::string& label, 
        ImDrawList * draw /* = nullptr */
    ) {
        if (label.empty()) return false;

        auto id = ImGui::GetID(label.c_str());
        float angle = ImGui::GetStateStorage()->GetFloat(id);
        int w, h;
        auto texture = ImModernUI::load_svg(
            "assets/icons/loader-circle.svg", 
            &w, 
            &h, 
            false, 
            ImVec4(0, 0, 0, 0), 
            true, 
            angle
        );

        auto pos = ImGui::GetCursorScreenPos();
        ImRect bb {
            pos.x, 
            pos.y, 
            pos.x + UISizes::size_4(), 
            pos.y + UISizes::size_4()
        };
        ImGui::ItemSize(bb.GetSize());

        if (draw == nullptr) draw = ImGui::GetWindowDrawList();
        draw->AddImage(
            texture, 
            bb.Min, 
            bb.Max
        );

        angle += ImGui::GetIO().DeltaTime * IM_PI * 2.0;
        ImGui::GetStateStorage()->SetFloat(id, angle);

        return true;
    }

    void ShowSpinnerExamples() {
        ImGuiChildFlags flags = ImGuiChildFlags_AutoResizeY;
        ImGui::BeginChild("##Spinner Examples", 
            ImVec2(0, 0), flags);

        Spinner("##Spinner 1");
        ImGui::SameLine();
        ImGui::TextUnformatted("Processing payment...");
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(UISizes::m_4(), 0));
        ImGui::SameLine();
        ImGui::TextUnformatted("$100.00");

        ImGui::EndChild();
    }
}