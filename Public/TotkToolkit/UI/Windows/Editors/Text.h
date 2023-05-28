#pragma once

#include <TotkToolkit/UI/Windows/Window.h>
#include <string>

namespace TotkToolkit::UI::Windows::Editors {
    class Text : public TotkToolkit::UI::Windows::Window {
public:
        Text(std::string name);

        virtual void DrawContents() override;

protected:
        std::string mText;
    };
}