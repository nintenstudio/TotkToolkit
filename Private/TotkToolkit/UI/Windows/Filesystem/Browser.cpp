#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>

#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <Formats/Aliases/Primitives.h>
#include <imgui.h>

namespace TotkToolkit::UI::Windows::Filesystem {
    Browser::Browser(bool* open) : TotkToolkit::UI::Windows::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER"), open) {
        mCurrentPath.push_back("Folder1");
        mCurrentPath.push_back("Folder2");
        mCurrentPath.push_back("Folder3");
    }

    void Browser::DrawContents() {
        //std::string currentPath = "";
        for (F_U32 i = 0; i < mCurrentPath.size(); i++) {
            ImGui::AlignTextToFramePadding();
            ImVec2 folderNameStartPos = ImGui::GetCursorPos();
            ImGui::TextDisabled(mCurrentPath.at(i).c_str());
            ImVec2 folderNameEndPos = ImGui::GetCursorPos();
            ImGui::SetCursorPos(folderNameStartPos);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
            if (ImGui::Button(AppendIdentifier("## Path Button " + std::to_string(i)).c_str(), ImGui::GetItemRectSize())) {
                ImGui::PopStyleColor();
                mCurrentPath.erase(mCurrentPath.begin() + i + 1, mCurrentPath.end());

            }
            else
                ImGui::PopStyleColor();
            ImGui::SetCursorPos(folderNameEndPos);

            ImGui::SameLine();
            ImGui::TextDisabled("/");
            ImGui::SameLine();
        }
    }
}