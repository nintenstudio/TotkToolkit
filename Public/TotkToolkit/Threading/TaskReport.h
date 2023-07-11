#pragma once

#include <Formats/Aliases/Primitives.h>
#include <string>
#include <vector>
#include <memory>
#include <shared_mutex>
#include <atomic>

namespace TotkToolkit::Threading {
    class TaskReport {
    public:
        TaskReport(std::string name);
        TaskReport(std::string name, F_U32 subTaskNum);
        TaskReport(std::string name, std::vector<std::shared_ptr<TaskReport>> childTaskReports);
        TaskReport(std::string name, F_U32 subTaskNum, std::vector<std::shared_ptr<TaskReport>> childTaskReports);

        F_F32 GetProgress();
        std::string GetName();
        std::string GetMessage();

        void SetMessage(std::string message);
        void AddProgress(F_F32 progress);
    private:
        std::string mName; std::shared_mutex mNameMutex;
        std::atomic<F_F32> mProgress;
        std::atomic<F_U32> mSubTaskNum;
        std::string mMessage; std::shared_mutex mMessageMutex;
        std::vector<std::shared_ptr<TaskReport>> mChildTaskReports; std::shared_mutex mChildTaskReportsMutex;
    };
}