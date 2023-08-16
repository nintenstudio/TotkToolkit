#include <TotkToolkit/UI/Windows/Filesystem/Browser.h>

#include <TotkToolkit/IO/FileHandle.h>
#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/MainWindow.h>
#include <TotkToolkit/UI/EditorSystem.h>
#include <TotkToolkit/UI/Windows/Editors/BYML.h>
#include <TotkToolkit/UI/Windows/Editors/TXTG.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <TotkToolkit/UI/Icons.h>
#include <TotkToolkit/UI/Fonts.h>
#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <Formats/Aliases/Primitives.h>
#include <Fallback/shared_ptr_atomic.h>
#include <imgui.h>
#include <future>

namespace TotkToolkit::UI::Windows::Filesystem {
    Browser::Browser(bool* open) : TotkToolkit::UI::Window(TotkToolkit::UI::Localization::TranslationSource::GetText("BROWSER"), open) {
        TotkToolkit::Messaging::NoticeBoard::AddReceiver(this);

        std::unique_lock<std::shared_mutex> lock(mSegmentedCurrentPathMutex);
        mSegmentedCurrentPath.push_back("romfs");
    }

    void Browser::DrawContents() {
        std::unique_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock1(mSegmentedCurrentPathMutex);
        std::shared_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock2(mCurrentFilesMutex);
        std::shared_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock3(mCurrentDirectoriesMutex);

        if (sMountArchivesTask.load() != nullptr) {
            ImGui::ProgressBar(sMountArchivesTask.load()->GetTaskReport()->GetProgress());
        }
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
        ImVec2 fileTableStart = ImGui::GetCursorPos();
        ImVec2 fileTableSize = ImGui::GetContentRegionAvail();
        if (itemsPerCol > 0) {
            if (ImGui::BeginTable(AppendIdentifier("File Table").c_str(), itemsPerCol, ImGuiTableFlags_SizingFixedSame | ImGuiTableColumnFlags_NoHeaderWidth)) {
                for (F_U32 i = 0; i < mCurrentDirectories.size(); i++) {
                    // Go to the next column
                    ImGui::TableNextColumn();

                    // Get the position we're at
                    ImVec2 itemPos = ImGui::GetCursorPos();
                    ImVec2 itemScreenPos = ImGui::GetCursorScreenPos();
                    
                    // Don't draw the item if it isn't in view
                    if (itemPos.y + itemWidth < ImGui::GetScrollY()) {
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemWidth);
                        continue;
                    }
                    if (itemPos.y > fileTableStart.y + ImGui::GetScrollY() + fileTableSize.y) {
                        // Just keep moving the cursor forward so it can still scroll
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemWidth);
                        continue;
                    }

                    // Make the actual button the user can click on
                    if (ImGui::InvisibleButton(("Directory " + mCurrentDirectories[i]).c_str(), ImVec2(itemWidth, itemWidth))) {
                        mSegmentedCurrentPath.push_back(mCurrentDirectories[i]);
                        UpdateItems();
                        break;
                    }

                    // Add hover effect to the button
                    if (ImGui::IsItemHovered()) {
                        ImVec2 hoverRectMin = ImVec2(itemScreenPos.x, itemScreenPos.y);
                        ImVec2 hoverRectMax = ImVec2(itemScreenPos.x + itemWidth, itemScreenPos.y + itemWidth);
                        ImVec4 hoverColor = ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered];
                        ImGui::GetWindowDrawList()->AddRectFilled(hoverRectMin, hoverRectMax, IM_COL32(hoverColor.x * 255, hoverColor.y * 255, hoverColor.z * 255, hoverColor.w * 255), ImGui::GetStyle().FrameRounding);
                    }

                    // Set the cursor back as if we never drew that invisible button
                    ImGui::SetCursorPos(itemPos);

                    // Draw the icon
                    ImGui::PushFont(TotkToolkit::UI::Fonts::sNormalFont2x);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemWidth / 2 - ImGui::GetFontSize() / 2);
                    ImGui::Text(TotkToolkit::UI::Icons::FOLDER_ICON);
                    ImGui::PopFont();

                    // Draw the name
                    ImGui::TextWrapped((mCurrentDirectories[i]).c_str());
                }
                for (F_U32 i = 0; i < mCurrentFiles.size(); i++) {
                    ImGui::PushID(i);

                    // Go the the next column
                    ImGui::TableNextColumn();

                    // Get the position we're at
                    ImVec2 itemPos = ImGui::GetCursorPos();
                    ImVec2 itemScreenPos = ImGui::GetCursorScreenPos();

                    // Don't draw the item if it isn't in view
                    if (itemPos.y + itemWidth < ImGui::GetScrollY()) {
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemWidth);
                        ImGui::PopID();
                        continue;
                    }
                    if (itemPos.y > fileTableStart.y + ImGui::GetScrollY() + fileTableSize.y) {
                        // Just keep moving the cursor forward so it can still scroll
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemWidth);
                        ImGui::PopID();
                        continue;
                    }

                    // Make the actual button the user can click on
                    if (ImGui::InvisibleButton(("File " + mCurrentFiles[i]).c_str(), ImVec2(itemWidth, itemWidth))) {
                        // TOTKTOOLKIT_TODO_FUNCTIONAL: Open with default editor for file extension
                    }

                    // Add hover effect to the button
                    if (ImGui::IsItemHovered()) {
                        ImVec2 hoverRectMin = ImVec2(itemScreenPos.x, itemScreenPos.y);
                        ImVec2 hoverRectMax = ImVec2(itemScreenPos.x + itemWidth, itemScreenPos.y + itemWidth);
                        ImVec4 hoverColor = ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered];
                        ImGui::GetWindowDrawList()->AddRectFilled(hoverRectMin, hoverRectMax, IM_COL32(hoverColor.x * 255, hoverColor.y * 255, hoverColor.z * 255, hoverColor.w * 255), ImGui::GetStyle().FrameRounding);
                    }

                    // Make right-click context menu appear for button
                    if (ImGui::BeginPopupContextItem()) {
                        ImGui::PushID("File Context Menu");
                        if (ImGui::BeginMenu("Open With")) {
                            ImGui::PushID("Open With");

                            if (ImGui::MenuItem("BYML Text")) {
                                std::string currentFilePath = GetCurrentPath() + mCurrentFiles[i];
                                std::shared_ptr<TotkToolkit::UI::Windows::Editors::BYML> editor = std::make_shared<TotkToolkit::UI::Windows::Editors::BYML>(TotkToolkit::IO::FileHandle(currentFilePath), mCurrentFiles[i], nullptr);
                                std::shared_ptr<Formats::IO::BinaryIOStreamBasic> fileStream = TotkToolkit::IO::Filesystem::GetReadStream(currentFilePath);
                                editor->Parse();
                                TotkToolkit::UI::EditorSystem::AddEditor(editor);
                            }
                            else if (ImGui::MenuItem("TXTG Texture")) {
                                std::string currentFilePath = GetCurrentPath() + mCurrentFiles[i];
                                std::shared_ptr<TotkToolkit::UI::Windows::Editors::TXTG> editor = std::make_shared<TotkToolkit::UI::Windows::Editors::TXTG>(TotkToolkit::IO::FileHandle(currentFilePath), mCurrentFiles[i], nullptr);
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

                    // Set the cursor back as if we never drew that invisible button
                    ImGui::SetCursorPos(itemPos);

                    // Draw the icon
                    ImGui::PushFont(TotkToolkit::UI::Fonts::sNormalFont2x);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + itemWidth / 2 - ImGui::GetFontSize() / 2);
                    ImGui::Text(TotkToolkit::UI::Icons::FILE_ICON);
                    ImGui::PopFont();

                    // Draw the name
                    ImGui::TextWrapped((mCurrentFiles[i]).c_str());

                    ImGui::PopID();
                }

                ImGui::EndTable();
            }
        }
    }

    std::string Browser::GetCurrentPath() {
        std::shared_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock(mSegmentedCurrentPathMutex);
        std::string res = "";

        for (std::string segment : mSegmentedCurrentPath)
            res += segment + "/";

        return res;
    }

    std::future<void> future;
    std::shared_ptr<std::atomic<bool>> futureContinueCondition;
    void Browser::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
        switch (notice->mType) {
            case TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_DUMPDIR: {
                std::shared_ptr<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::DumpDir> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::DumpDir>(notice);

                if (futureContinueCondition)
                    *futureContinueCondition = false;
                futureContinueCondition = std::make_shared<std::atomic<bool>>(true);

                TotkToolkit::IO::Filesystem::InitThread();
                TotkToolkit::IO::Filesystem::SyncThread();
                sMountArchivesTask = std::make_shared<TotkToolkit::Threading::Tasks::IO::Filesystem::MountArchives>([this]() -> void {/*sMountArchivesTask.store(nullptr);*/ }, futureContinueCondition);
                future = std::async(std::launch::async, []() -> void {sMountArchivesTask.load()->Execute();});
                return;
            }
            case TotkToolkit::Messaging::NoticeType::IO_FILESYSTEM_FILESCHANGE: {
                std::shared_ptr<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>(notice);

                TotkToolkit::IO::Filesystem::InitThread();
                TotkToolkit::IO::Filesystem::SyncThread();
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
        TotkToolkit::IO::Filesystem::InitThread();
        TotkToolkit::IO::Filesystem::SyncThread();

        std::vector<std::string> currentFiles = TotkToolkit::IO::Filesystem::EnumerateFiles(GetCurrentPath());

        std::unique_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock(mCurrentFilesMutex);
        mCurrentFiles = currentFiles;
    }

    void Browser::UpdateDirectories() {
        TotkToolkit::IO::Filesystem::InitThread();
        TotkToolkit::IO::Filesystem::SyncThread();

        std::vector<std::string> currentDirectories = TotkToolkit::IO::Filesystem::EnumerateDirectories(GetCurrentPath());

        std::unique_lock<TotkToolkit::Threading::Mutexes::SharedRecursive> lock(mCurrentDirectoriesMutex);
        mCurrentDirectories = currentDirectories;
    }

    std::atomic<std::shared_ptr<TotkToolkit::Threading::Tasks::IO::Filesystem::MountArchives>> Browser::sMountArchivesTask = nullptr;
}