#include <TotkToolkit/UI/MainWindow.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>

namespace TotkToolkit::UI {
    MainWindow::MainWindow() : TotkToolkit::UI::ImGuiItem::ImGuiItem(), mBrowser(&mBrowserOpen), mSettings(&mSettingsOpen) {

    }

    void MainWindow::Draw() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("FILE")).c_str())) {
                
            }
            if (ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("EDIT")).c_str())) {
                
            }
            if (ImGui::BeginMenu(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("SETTINGS")).c_str())) {
                mSettings.DrawContents();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("WINDOWS")).c_str())) {
                ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER")).c_str(), nullptr, &mBrowserOpen, true);
                ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("SETTINGS")).c_str(), nullptr, &mSettingsOpen, true);
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();

        if (mBrowserOpen)
            mBrowser.Draw();
        if (mSettingsOpen)
            mSettings.Draw();
    }
}