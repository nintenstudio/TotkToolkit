#pragma once

#include <TotkToolkit/UI/ImGuiItem.h>

#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>
#include <TotkToolkit/UI/Windows/Configuration/Settings.h>
#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/Messaging/Receiver.h>

#include <vector>
#include <memory>

namespace TotkToolkit::UI {
    class MainWindow : public TotkToolkit::UI::ImGuiItem, public TotkToolkit::Messaging::Receiver {
public:
        MainWindow();

        virtual void Draw() override;

        virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) override;

        std::vector<std::shared_ptr<TotkToolkit::UI::Window>> mEditors;

protected:
        TotkToolkit::UI::Windows::Filesystem::Browser mBrowser;
        TotkToolkit::UI::Windows::Configuration::Settings mSettings;

        bool mBrowserOpen = true;
        bool mSettingsOpen = false;
    };
}