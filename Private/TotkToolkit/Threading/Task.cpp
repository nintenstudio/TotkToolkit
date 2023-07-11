#include <TotkToolkit/Threading/Task.h>

namespace TotkToolkit::Threading {
    Task::Task(std::function<void()> callback, std::shared_ptr<TotkToolkit::Threading::TaskReport> taskReport) : mCallback(callback), mTaskReport(taskReport) {

    }

    std::shared_ptr<TotkToolkit::Threading::TaskReport> Task::GetTaskReport() {
        return mTaskReport;
    }
}