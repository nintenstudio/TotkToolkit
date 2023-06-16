#pragma once

#include <TotkToolkit/UI/Window.h>

#include <string>

namespace TotkToolkit::UI::Windows::Configuration {
    class Settings : public TotkToolkit::UI::Window {
    public:
        Settings(bool* open);

        virtual void DrawContents() override;
    };
}