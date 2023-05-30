#pragma once

#include <TotkToolkit/UI/Windows/Window.h>

#include <vector>
#include <string>

namespace TotkToolkit::UI::Windows::Filesystem {
    class Browser : public TotkToolkit::UI::Windows::Window {
public:
        Browser(bool* open);

        virtual void DrawContents() override;

private:
        std::vector<std::string> mCurrentPath;
    };
}