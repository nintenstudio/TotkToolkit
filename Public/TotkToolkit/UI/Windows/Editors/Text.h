#pragma once

#include <TotkToolkit/UI/Windows/Window.h>
#include <TotkToolkit/IO/Editor.h>

#include <string>

namespace TotkToolkit::UI::Windows::Editors {
    class Text : public TotkToolkit::UI::Windows::Window, public TotkToolkit::IO::Editor {
public:
        Text(std::string name);

        virtual void DrawContents() override;

protected:
        std::string mText;
    };
}