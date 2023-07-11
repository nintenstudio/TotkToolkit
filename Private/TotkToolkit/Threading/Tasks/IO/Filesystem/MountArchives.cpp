#include <TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/UI/Localization/TranslationSource.h>
#include <Formats/Aliases/Primitives.h>
#include <filesystem>

namespace TotkToolkit::Threading::Tasks::IO::Filesystem {
    MountArchives::MountArchives() : TotkToolkit::Threading::Task(nullptr, std::make_shared<TotkToolkit::Threading::TaskReport>(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNT_ARCHIVES"))) {

    }
    MountArchives::MountArchives(std::function<void()> callback) : TotkToolkit::Threading::Task(callback, std::make_shared<TotkToolkit::Threading::TaskReport>(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNT_ARCHIVES"))) {

    }

    void MountArchives::Execute() {
        mTaskReport->SetMessage(TotkToolkit::UI::Localization::TranslationSource::GetText("MOUNTING_PACKS"));
        std::vector<std::string> packPaths = TotkToolkit::IO::Filesystem::SearchFilenamesByExtension("", ".pack.zs"); // Equivilent to regex search for R"(\.pack\.zs$)" but faster
        for (std::string packPath : packPaths) {
            TotkToolkit::IO::Filesystem::Mount((std::filesystem::path(TotkToolkit::IO::Filesystem::GetRealDir(packPath.c_str())) / std::filesystem::path(packPath)).generic_string());
            mTaskReport->AddProgress(1.f / packPaths.size());
        }

        mCallback();
    }
}