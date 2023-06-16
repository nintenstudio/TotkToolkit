#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>

#include <TotkToolkit/IO/FileHandle.h>
#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/MainWindow.h>
#include <TotkToolkit/UI/EditorSystem.h>
#include <TotkToolkit/UI/Windows/Editors/BYML.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <TotkToolkit/UI/Icons.h>
#include <TotkToolkit/UI/Fonts.h>
#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <Formats/Aliases/Primitives.h>
#include <imgui.h>

namespace TotkToolkit::UI::Windows::Filesystem {
    Browser::Browser(bool* open) : TotkToolkit::UI::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER"), open) {
        TotkToolkit::Messaging::NoticeBoard::AddReceiver(this);
        mSegmentedCurrentPath.push_back("romfs");
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
            if (ImGui::Button(AppendIdentifier("", "Path Button " + std::to_string(i)).c_str(), ImGui::GetItemRectSize())) {
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

        float itemWidth = 4 * ImGui::GetFontSize();
        int itemsPerCol = (ImGui::GetContentRegionAvail().x / itemWidth) - 1;
        if (itemsPerCol > 0) {
            if (ImGui::BeginTable(AppendIdentifier("File Table").c_str(), itemsPerCol, ImGuiTableFlags_SizingFixedSame | ImGuiTableColumnFlags_NoHeaderWidth)) {
                for (F_U32 i = 0; i < mCurrentDirectories.size(); i++) {
                    ImGui::TableNextColumn();
                    ImVec2 itemPos = ImGui::GetCursorPos();
                    ImVec2 itemScreenPos = ImGui::GetCursorScreenPos();
                    if (ImGui::InvisibleButton(("Directory " + mCurrentDirectories[i]).c_str(), ImVec2(itemWidth, itemWidth))) {
                        mSegmentedCurrentPath.push_back(mCurrentDirectories[i]);
                        UpdateItems();
                        break;
                    }
                    if (ImGui::IsItemHovered()) {
                        ImVec2 hoverRectMin = ImVec2(itemScreenPos.x, itemScreenPos.y);
                        ImVec2 hoverRectMax = ImVec2(itemScreenPos.x + itemWidth, itemScreenPos.y + itemWidth);
                        ImVec4 hoverColor = ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered];
                        ImGui::GetWindowDrawList()->AddRectFilled(hoverRectMin, hoverRectMax, IM_COL32(hoverColor.x * 255, hoverColor.y * 255, hoverColor.z * 255, hoverColor.w * 255), ImGui::GetStyle().FrameRounding);
                    }
                    ImGui::SetCursorPos(itemPos);
                    ImGui::PushFont(TotkToolkit::UI::Fonts::sNormalFont2x);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemWidth / 2 - ImGui::GetFontSize() / 2);
                    ImGui::Text(TotkToolkit::UI::Icons::FOLDER_ICON);
                    ImGui::PopFont();
                    ImGui::TextWrapped((mCurrentDirectories[i]).c_str());
                }
                for (F_U32 i = 0; i < mCurrentFiles.size(); i++) {
                    ImGui::PushID(i);

                    ImGui::TableNextColumn();
                    ImVec2 itemPos = ImGui::GetCursorPos();
                    ImVec2 itemScreenPos = ImGui::GetCursorScreenPos();
                    if (ImGui::InvisibleButton(("File " + mCurrentFiles[i]).c_str(), ImVec2(itemWidth, itemWidth))) {
                        // TOTKTOOLKIT_TODO_FUNCTIONAL: Open with default editor for file extension
                    }
                    if (ImGui::BeginPopupContextWindow()) {
                        ImGui::PushID("File Context Menu");
                        if (ImGui::BeginMenu("Open With")) {
                            ImGui::PushID("Open With");

                            if (ImGui::MenuItem("BYML Text")) {
                                std::string currentFilePath = GetCurrentPath() + mCurrentFiles[i];
                                std::shared_ptr<TotkToolkit::UI::Windows::Editors::BYML> editor = std::make_shared<TotkToolkit::UI::Windows::Editors::BYML>(TotkToolkit::IO::FileHandle::FileHandle(currentFilePath), mCurrentFiles[i], nullptr);
                                std::shared_ptr<Formats::IO::BinaryIOStreamBasic> fileStream = TotkToolkit::IO::Filesystem::GetReadStream(currentFilePath);
                                editor->Parse();
                                TotkToolkit::UI::EditorSystem::AddEditor(editor);
                            }

                            ImGui::PopID();
                            ImGui::EndMenu();
                        }
                        
                        ImGui::PopID();
                        ImGui::EndPopup();
                    }
                    if (ImGui::IsItemHovered()) {
                        ImVec2 hoverRectMin = ImVec2(itemScreenPos.x, itemScreenPos.y);
                        ImVec2 hoverRectMax = ImVec2(itemScreenPos.x + itemWidth, itemScreenPos.y + itemWidth);
                        ImVec4 hoverColor = ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered];
                        ImGui::GetWindowDrawList()->AddRectFilled(hoverRectMin, hoverRectMax, IM_COL32(hoverColor.x * 255, hoverColor.y * 255, hoverColor.z * 255, hoverColor.w * 255), ImGui::GetStyle().FrameRounding);
                    }
                    ImGui::SetCursorPos(itemPos);
                    ImGui::PushFont(TotkToolkit::UI::Fonts::sNormalFont2x);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemWidth / 2 - ImGui::GetFontSize() / 2);
                    ImGui::Text(TotkToolkit::UI::Icons::FILE_ICON);
                    ImGui::PopFont();
                    ImGui::TextWrapped((mCurrentFiles[i]).c_str());

                    ImGui::PopID();
                }

                ImGui::EndTable();
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
        switch (notice->mType) {
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
        UpdateFiles();
        UpdateDirectories();
    }

    void Browser::UpdateFiles () {
        mCurrentFiles = TotkToolkit::IO::Filesystem::EnumerateFiles(GetCurrentPath());
    }

    void Browser::UpdateDirectories() {
        mCurrentDirectories = TotkToolkit::IO::Filesystem::EnumerateDirectories(GetCurrentPath());
    }
}