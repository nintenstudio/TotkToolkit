#include <TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <Formats/Aliases/Primitives.h>
#include <filesystem>

namespace TotkToolkit::Threading::Tasks::IO::Filesystem {
    MountArchives::MountArchives(std::function<void()> callback, std::shared_ptr<std::atomic<bool>> continueCondition) : TotkToolkit::Threading::Task(callback, continueCondition, std::make_shared<TotkToolkit::Threading::TaskReport>(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNT_ARCHIVES"))) {

    }

    void MountArchives::Execute() {
        mTaskReport->SetMessage(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNTING_PACKS"));
        std::vector<std::string> packPaths = TotkToolkit::IO::Filesystem::SearchFilenamesByExtension("", ".pack.zs", mContinueCondition); // Equivilent to regex search for R"(\.pack\.zs$)" but faster
        for (std::string packPath : packPaths) {
            if (!*mContinueCondition)
                return;

            TotkToolkit::IO::Filesystem::Mount((std::filesystem::path(TotkToolkit::IO::Filesystem::GetRealDir(packPath.c_str())) / std::filesystem::path(packPath)).generic_string(), "romfs");
            mTaskReport->AddProgress(1.f / packPaths.size());
        }

        mCallback();
    }
}