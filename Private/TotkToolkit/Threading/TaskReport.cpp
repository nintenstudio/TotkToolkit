#include <TotkToolkit/Threading/TaskReport.h>

namespace TotkToolkit::Threading {
    TaskReport::TaskReport(std::string name) : mName(name), mProgress(0.f), mSubTaskNum(1), mChildTaskReports() {

    }
    TaskReport::TaskReport(std::string name, F_U32 subTaskNum) : mName(name), mProgress(0.f), mSubTaskNum(subTaskNum), mChildTaskReports() {

    }
    TaskReport::TaskReport(std::string name, std::vector<std::shared_ptr<TaskReport>> childTaskReports) : mName(name), mProgress(0.f), mSubTaskNum(1), mChildTaskReports(childTaskReports) {

    }
    TaskReport::TaskReport(std::string name, F_U32 subTaskNum, std::vector<std::shared_ptr<TaskReport>> childTaskReports) : mName(name), mProgress(0.f), mSubTaskNum(subTaskNum), mChildTaskReports(childTaskReports) {

    }

    F_F32 TaskReport::GetProgress() {
        if (mChildTaskReports.size() > 0) {
            F_F32 progress = 0.0f;
            for (std::shared_ptr<TaskReport> childTaskReport : mChildTaskReports) {
                progress += childTaskReport->GetProgress();
            }
            progress /= mChildTaskReports.size();
            return (progress + mProgress) / 2;
        }
        return mProgress;
    }
    std::string TaskReport::GetName() {
        std::shared_lock<std::shared_mutex> lock(mNameMutex);
        return mName;
    }
    std::string TaskReport::GetMessage() {
        std::shared_lock<std::shared_mutex> lock(mMessageMutex);
        return mMessage;
    }

    void TaskReport::SetMessage(std::string message) {
        std::unique_lock<std::shared_mutex> lock(mMessageMutex);
        mMessage = message;
    }
    void TaskReport::AddProgress(F_F32 progress) {
        mProgress = mProgress.load() + progress / mSubTaskNum;
    }
}