#pragma once

#include <TotkToolkit/Threading/TaskReport.h>
#include <functional>
#include <memory>
#include <atomic>

namespace TotkToolkit::Threading {
    class Task {
    public:
        Task(std::function<void()> callback, std::shared_ptr<std::atomic<bool>> continueCondition, std::shared_ptr<TotkToolkit::Threading::TaskReport> taskReport);

        std::shared_ptr<TotkToolkit::Threading::TaskReport> GetTaskReport();

        virtual void Execute() = 0;
    protected:
        const std::shared_ptr<TotkToolkit::Threading::TaskReport> mTaskReport; // TOTKTOOLKIT_CONSIDERATION_THREAD_SAFETY: Does not need to be marked atomic because it is initialized when the object is constructed on the calling thread, and then not mutated.
        std::function<void()> mCallback;
        std::shared_ptr<std::atomic<bool>> mContinueCondition;
    };
}