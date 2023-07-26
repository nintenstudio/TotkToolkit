#include <TotkToolkit/IO/PHYSFSCalls/Mount.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <physfs.h>

namespace TotkToolkit::IO::PHYSFSCalls {
    void Mount::Execute() {
        if (PHYSFS_mount(mPath.c_str(), mMountPoint.c_str(), mAppendToPath))
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
    }
}