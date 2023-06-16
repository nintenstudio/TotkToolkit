#include <TotkToolkit/UI/Windows/Configuration/Settings.h>

#include <TotkToolkit/Configuration/Settings.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace TotkToolkit::UI::Windows::Configuration {
    Settings::Settings(bool* open) : TotkToolkit::UI::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("SETTINGS"), open) {
    }

    void Settings::DrawContents() {
        std::string romfsDir = TotkToolkit::Configuration::Settings::GetRomfsDir();
        ImGui::InputText(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("GAME_DUMP_DIR")).c_str(), &romfsDir);
        TotkToolkit::Configuration::Settings::SetRomfsDir(romfsDir);
    }
}