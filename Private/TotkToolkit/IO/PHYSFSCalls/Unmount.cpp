#include <TotkToolkit/IO/PHYSFSCalls/Unmount.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <physfs.h>

namespace TotkToolkit::IO::PHYSFSCalls {
    void Unmount::Execute() {
        if (PHYSFS_unmount(mPath.c_str()))
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
    }
}