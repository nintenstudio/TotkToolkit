#pragma once

#include <TotkToolkit/UI/Windows/Window.h>
#include <TotkToolkit/Messaging/Receiver.h>

#include <vector>
#include <string>

namespace TotkToolkit::UI::Windows::Filesystem {
    class Browser : public TotkToolkit::UI::Windows::Window, public TotkToolkit::Messaging::Receiver {
public:
        Browser(bool* open);

        virtual void DrawContents() override;

        std::string GetCurrentPath();

        virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) override;

protected:
        void UpdateItems();

        std::vector<std::string> mSegmentedCurrentPath;
        std::vector<std::string> mCurrentItems;
    };
}