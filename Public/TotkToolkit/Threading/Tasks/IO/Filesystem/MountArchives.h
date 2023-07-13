#include <TotkToolkit/Threading/Task.h>

namespace TotkToolkit::Threading::Tasks::IO::Filesystem {
    class MountArchives : public TotkToolkit::Threading::Task {
    public:
        MountArchives(std::function<void()> callback = nullptr, std::shared_ptr<std::atomic<bool>> continueCondition = std::make_shared<std::atomic<bool>>(true));

        virtual void Execute() override;
    };
}