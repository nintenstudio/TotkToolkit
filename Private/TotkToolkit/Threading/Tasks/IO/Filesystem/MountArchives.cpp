#include <TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <Formats/Aliases/Primitives.h>
#include <filesystem>
#include <memory>

namespace TotkToolkit::Threading::Tasks::IO::Filesystem {
    MountArchives::MountArchives(std::function<void()> callback, std::shared_ptr<std::atomic<bool>> continueCondition) : TotkToolkit::Threading::Task(callback, continueCondition, std::make_shared<TotkToolkit::Threading::TaskReport>(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNT_ARCHIVES"))) {

    }

    void MountArchives::Execute() {
        mTaskReport->SetMessage(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNTING_PACKS"));

        TotkToolkit::IO::Filesystem::InitThread();
        TotkToolkit::IO::Filesystem::SyncThread();
        std::vector<std::string> packPaths = TotkToolkit::IO::Filesystem::SearchFilenamesByExtension("", ".pack.zs", mContinueCondition); // Equivilent to regex search for R"(\.pack\.zs$)" but faster
        for (std::string packPath : packPaths) {
            if (!*mContinueCondition)
                return;

            std::shared_ptr<Formats::IO::Stream> pack = TotkToolkit::IO::Filesystem::GetReadStream(packPath);
            if (pack != nullptr)
                TotkToolkit::IO::Filesystem::MountStream(pack, std::filesystem::path(packPath).filename().generic_string(), "romfs", false);
            mTaskReport->AddProgress(1.f / packPaths.size());
        }

        // Since we bypassed the notice on each mount for performance reasons
        TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());

        mCallback();
    }
}