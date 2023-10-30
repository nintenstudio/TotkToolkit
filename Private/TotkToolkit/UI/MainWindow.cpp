#include <TotkToolkit/UI/MainWindow.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <imgui.h>

// TODO: Actually implement file opening system.
#include <TotkToolkit/UI/Windows/Editors/BYML.h>
#include <TotkToolkit/IO/Filesystem.h>

namespace TotkToolkit::UI {
    MainWindow::MainWindow() : TotkToolkit::UI::ImGuiItem::ImGuiItem(), mBrowser(&mBrowserOpen), mSettings(&mSettingsOpen), mStyle(&mStyleOpen) {
        TotkToolkit::Messaging::NoticeBoard::AddReceiver(this);
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
                ImGui::MenuItem(AppendIdentifier(TotkToolkit::UI::Localization::TranslationSource::GetText("STYLE")).c_str(), nullptr, &mStyleOpen, true);
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();

        if (mBrowserOpen)
            mBrowser.Draw();
        if (mSettingsOpen)
            mSettings.Draw();
        if (mStyleOpen)
            mStyle.Draw();

        for (std::shared_ptr<TotkToolkit::UI::Window> window : mEditors) {
            window->Draw();
        }
    }

    void MainWindow::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
        switch (notice->mType){
            default:
                return;
        }
    }
}