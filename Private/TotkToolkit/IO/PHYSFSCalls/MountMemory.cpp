#include <TotkToolkit/IO/PHYSFSCalls/MountMemory.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <physfs.h>

namespace TotkToolkit::IO::PHYSFSCalls {
    void MountMemory::Execute() {
        if (PHYSFS_mountMemory(mBuffer.get(), mBufferLength, mDeleteCallback, mNewDir.c_str(), mMountPoint.c_str(), mAppendToPath))
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
    }
}