#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <Formats/Aliases/Primitives.h>
#include <imgui.h>

namespace TotkToolkit::UI::Windows::Filesystem {
    Browser::Browser(bool* open) : TotkToolkit::UI::Windows::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER"), open) {
        TotkToolkit::Messaging::NoticeBoard::AddReceiver(this);
        mSegmentedCurrentPath.push_back("");
    }

    void Browser::DrawContents() {
        //std::string currentPath = "";
        for (F_U32 i = 0; i < mSegmentedCurrentPath.size(); i++) {
            ImGui::AlignTextToFramePadding();
            ImVec2 folderNameStartPos = ImGui::GetCursorPos();
            ImGui::TextDisabled(mSegmentedCurrentPath.at(i).c_str());
            ImVec2 folderNameEndPos = ImGui::GetCursorPos();
            ImGui::SetCursorPos(folderNameStartPos);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
            if (ImGui::Button(AppendIdentifier("## Path Button " + std::to_string(i)).c_str(), ImGui::GetItemRectSize())) {
                ImGui::PopStyleColor();
                mSegmentedCurrentPath.erase(mSegmentedCurrentPath.begin() + i + 1, mSegmentedCurrentPath.end());
                UpdateItems();
            }
            else
                ImGui::PopStyleColor();
            ImGui::SetCursorPos(folderNameEndPos);

            ImGui::SameLine();
            ImGui::TextDisabled("/");
            ImGui::SameLine();
        }

        ImGui::NewLine();

        for (F_U32 i = 0; i < mCurrentItems.size(); i++) {
            if (ImGui::Button(mCurrentItems[i].c_str())) {
                mSegmentedCurrentPath.push_back(mCurrentItems[i]);
                UpdateItems();
            }
        }
    }

    std::string Browser::GetCurrentPath() {
        std::string res = "";

        for (std::string segment : mSegmentedCurrentPath)
            res += segment + "/";

        return res;
    }

    void Browser::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
        switch (notice->mNoticeType) {
            case TotkToolkit::Messaging::NoticeType::IO_FILESYSTEM_FILESCHANGE: {
                std::shared_ptr<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>(notice);

                UpdateItems();
                return;
            }
            default:
                return;
        }
    }

    void Browser::UpdateItems() {
        mCurrentItems = TotkToolkit::IO::Filesystem::EnumerateFiles(GetCurrentPath());
    }
}