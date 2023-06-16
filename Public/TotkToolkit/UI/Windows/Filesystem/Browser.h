#pragma once

#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/Messaging/Receiver.h>

#include <vector>
#include <string>

namespace TotkToolkit::UI::Windows::Filesystem {
    class Browser : public TotkToolkit::UI::Window, public TotkToolkit::Messaging::Receiver {
public:
        Browser(bool* open);

        virtual void DrawContents() override;

        std::string GetCurrentPath();

        virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) override;

protected:
        void UpdateItems();
        void UpdateFiles();
        void UpdateDirectories();

        std::vector<std::string> mSegmentedCurrentPath;
        std::vector<std::string> mCurrentFiles;
        std::vector<std::string> mCurrentDirectories;
    };
}