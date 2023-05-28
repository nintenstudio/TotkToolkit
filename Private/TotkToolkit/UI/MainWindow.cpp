#include <TotkToolkit/UI/MainWindow.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>

namespace TotkToolkit::UI {
    MainWindow::MainWindow() : TotkToolkit::UI::ImGuiItem::ImGuiItem() {

    }

    void MainWindow::Draw() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("FILE")).c_str())) {
                
            }
            if (ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("EDIT")).c_str())) {
                
            }
            if (ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("SETTINGS")).c_str())) {
                
            }
            if (ImGui::BeginMenu(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("WINDOWS")).c_str())) {
                ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER")).c_str(), nullptr, &mBrowserEnabled, true);
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();

        if (mBrowserEnabled)
            mBrowser.Draw();
    }
}