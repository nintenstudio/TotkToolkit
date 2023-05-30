#include <TotkToolkit/UI/Windows/Configuration/Settings.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace TotkToolkit::UI::Windows::Configuration {
    Settings::Settings(bool* open) : TotkToolkit::UI::Windows::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("SETTINGS"), open) {
    }

    void Settings::DrawContents() {
        ImGui::InputText(AppendIdentifier("Romfs Dir").c_str(), &mRomfsDir);
    }
}