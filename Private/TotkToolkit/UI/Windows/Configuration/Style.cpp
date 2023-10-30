#include <TotkToolkit/UI/Windows/Configuration/Style.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace TotkToolkit::UI::Windows::Configuration {
    Style::Style(bool* open) : TotkToolkit::UI::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("STYLE"), open) {
    }

    void Style::DrawContents() {
        ImGui::ShowStyleEditor();
    }
}