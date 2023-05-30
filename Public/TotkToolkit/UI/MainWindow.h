#pragma once

#include <TotkToolkit/UI/ImGuiItem.h>

#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>
#include <TotkToolkit/UI/Windows/Configuration/Settings.h>

namespace TotkToolkit::UI {
    class MainWindow : public TotkToolkit::UI::ImGuiItem {
public:
        MainWindow();

        virtual void Draw() override;

protected:
        TotkToolkit::UI::Windows::Filesystem::Browser mBrowser;
        TotkToolkit::UI::Windows::Configuration::Settings mSettings;

        bool mBrowserOpen = true;
        bool mSettingsOpen = false;
    };
}