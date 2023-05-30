#pragma once

#include <TotkToolkit/UI/ImGuiItem.h>

#include <string>

namespace TotkToolkit::UI::Windows {
    class Window : public TotkToolkit::UI::ImGuiItem {
public:
    Window(std::string name, bool* open);
    
    virtual void Draw() override;
    virtual void DrawContents() {};

protected:
    std::string mName;
    bool* mOpen;
    };
}