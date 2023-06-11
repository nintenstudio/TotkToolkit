#pragma once

#include <TotkToolkit/UI/Windows/Window.h>

#include <string>

namespace TotkToolkit::UI::Windows::Configuration {
    class Settings : public TotkToolkit::UI::Windows::Window {
    public:
        Settings(bool* open);

        virtual void DrawContents() override;
    };
}