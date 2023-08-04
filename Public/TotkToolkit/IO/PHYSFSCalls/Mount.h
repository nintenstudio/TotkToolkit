#pragma once

#include <TotkToolkit/IO/PHYSFSCall.h>

#include <string>

namespace TotkToolkit::IO::PHYSFSCalls {
    class Mount : public TotkToolkit::IO::PHYSFSCall {
    public:
        Mount(std::string path, std::string mountPoint, bool appendToPath, bool notifyFileChange = true) : mPath(path), mMountPoint(mountPoint), mAppendToPath(appendToPath), mNotifyFileChange(notifyFileChange) {

        }

        virtual void Execute() override;

    protected:
        std::string mPath;
        std::string mMountPoint;
        bool mAppendToPath;
        bool mNotifyFileChange;
    };
}