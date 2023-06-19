#pragma once

#include <TotkToolkit/UI/ImGuiItem.h>

#include <string>
#include <imgui.h>

namespace TotkToolkit::UI {
    class Window : public TotkToolkit::UI::ImGuiItem {
public:
        Window(std::string name, bool* open);
    
        virtual void Draw() override;
        virtual void DrawContents() {};

        bool IsOpen();

protected:
        std::string mName;
        ImGuiWindowFlags mWindowFlags;
        bool* mOpen;
        bool mOpenLocal;
    };
}