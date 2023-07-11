#include <TotkToolkit/Threading/Task.h>

namespace TotkToolkit::Threading::Tasks::IO::Filesystem {
    class MountArchives : public TotkToolkit::Threading::Task {
    public:
        MountArchives();
        MountArchives(std::function<void()> callback);

        virtual void Execute() override;
    };
}