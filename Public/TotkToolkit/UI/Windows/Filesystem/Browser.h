#pragma once

#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/Messaging/Receiver.h>

#include <TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.h>
#include <TotkToolkit/Threading/Mutexes/SharedRecursive.h>
#include <vector>
#include <string>
#include <memory>
#include <atomic>

namespace TotkToolkit::UI::Windows::Filesystem {
    class Browser : public TotkToolkit::UI::Window, public TotkToolkit::Messaging::Receiver {
    public:
        Browser(bool* open);

        virtual void DrawContents() override;

        std::string GetCurrentPath();

        virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) override;

    protected:
        void UpdateItems();
        void UpdateFiles();
        void UpdateDirectories();

        std::vector<std::string> mSegmentedCurrentPath; TotkToolkit::Threading::Mutexes::SharedRecursive mSegmentedCurrentPathMutex; // Should always be acquired first to avoid deadlock.
        std::vector<std::string> mCurrentFiles; TotkToolkit::Threading::Mutexes::SharedRecursive mCurrentFilesMutex; // Should always be acquired second to avoid deadlock.
        std::vector<std::string> mCurrentDirectories; TotkToolkit::Threading::Mutexes::SharedRecursive mCurrentDirectoriesMutex; // Should always be acquired third to avoid deadlock.

        static std::atomic<std::shared_ptr<TotkToolkit::Threading::Tasks::IO::Filesystem::MountArchives>> sMountArchivesTask; // TOTKTOOLKIT_FUNCTIONAL_CONSIDERATION_THREAD_SAFETY: Our callback modifies this, and that's run on the task thread.
    };
}