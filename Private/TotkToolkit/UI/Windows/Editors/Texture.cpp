#include <TotkToolkit/UI/Windows/Editors/Texture.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <imgui.h>

namespace TotkToolkit::UI::Windows::Editors {
    Texture::Texture(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editor(fileHandle, name, open) {

    }
    Texture::Texture(std::shared_ptr<Formats::Resource> resource, std::string name, bool* open) : TotkToolkit::UI::Windows::Editor(resource, name, open) {

    }

    void Texture::DrawContents() {
        TotkToolkit::UI::Windows::Editor::DrawContents();

        ImVec2 toolbarCursorStart = ImGui::GetCursorPos();
        // Any sort of toolbar code can be put here.
        ImVec2 toolbarCursorEnd = ImGui::GetCursorPos();

        ImVec2 windowContentRegionSize;
        {
            ImVec2 windowContentRegionMin = ImGui::GetWindowContentRegionMin();
            ImVec2 windowContentRegionMax = ImGui::GetWindowContentRegionMax();

            windowContentRegionSize.x = windowContentRegionMax.x - windowContentRegionMin.x;
            windowContentRegionSize.y = windowContentRegionMax.y - windowContentRegionMin.y;
        }

        ImVec2 toolbarSize = toolbarCursorEnd;
        toolbarSize.x -= toolbarCursorStart.x;
        toolbarSize.y -= toolbarCursorStart.y;



        ImVec2 imageSize = windowContentRegionSize;
        imageSize.x -= toolbarSize.x;
        imageSize.y -= toolbarSize.y;
        ImGui::Image(mTextureID, imageSize);
    }
}