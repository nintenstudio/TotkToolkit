#include <TotkToolkit/UI/Windows/Window.h>

#include <TotkToolkit/UI/Windows/Window.h>

#include <imgui.h>

namespace TotkToolkit::UI::Windows {
    Window::Window(std::string name, bool* open) : mName(name), mOpen(open), TotkToolkit::UI::ImGuiItem::ImGuiItem() {

    }

    void Window::Draw() {
        ImGui::Begin(AppendIdentifier(mName).c_str(), mOpen);
        DrawContents();
        ImGui::End();
    }
}