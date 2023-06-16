#include <TotkToolkit/UI/Window.h>

#include <TotkToolkit/UI/Window.h>

#include <imgui.h>

namespace TotkToolkit::UI {
    Window::Window(std::string name, bool* open) : mName(name), mOpen(open), mOpenLocal(true), TotkToolkit::UI::ImGuiItem::ImGuiItem() {
        if (open == nullptr)
            mOpen = &mOpenLocal;
    }

    void Window::Draw() {
        ImGui::Begin(AppendIdentifier(mName).c_str(), mOpen);
        DrawContents();
        ImGui::End();
    }

    bool Window::IsOpen() {
        return *mOpen;
    }
}