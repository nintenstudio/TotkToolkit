#pragma once

#include <TotkToolkit/UI/Window.h>

#include <string>

namespace TotkToolkit::UI::Windows::Configuration {
    class Style : public TotkToolkit::UI::Window {
    public:
        Style(bool* open);

        virtual void DrawContents() override;
    };
}