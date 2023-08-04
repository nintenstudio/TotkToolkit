#include <TotkToolkit/IO/PHYSFSCalls/SetWriteDir.h>

#include <physfs.h>

namespace TotkToolkit::IO::PHYSFSCalls {
    void SetWriteDir::Execute() {
        PHYSFS_setWriteDir(mWriteDir.c_str());
    }
}