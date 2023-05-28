#include <TotkToolkit/UI/Windows/Window.h>

#include <TotkToolkit/UI/Windows/Window.h>

#include <imgui.h>

namespace TotkToolkit::UI::Windows {
    Window::Window(std::string name) : mName(name), TotkToolkit::UI::ImGuiItem::ImGuiItem() {

    }

    void Window::Draw() {
        ImGui::Begin(mName.c_str());
        DrawContents();
        ImGui::End();
    }
}