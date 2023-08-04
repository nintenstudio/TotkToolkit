#pragma once

#include <TotkToolkit/IO/PHYSFSCall.h>

#include <Formats/Aliases/Primitives.h>
#include <physfs.h>
#include <string>
#include <memory>

namespace TotkToolkit::IO::PHYSFSCalls {
    class MountMemory : public TotkToolkit::IO::PHYSFSCall {
    public:
        MountMemory(std::shared_ptr<F_U8[]> buffer, PHYSFS_uint64 bufferLength, void (*deleteCallback)(void*), std::string newDir, std::string mountPoint, bool appendToPath, bool notifyFileChange = true) : mBuffer(buffer), mBufferLength(bufferLength), mDeleteCallback(deleteCallback), mNewDir(newDir), mMountPoint(mountPoint), mAppendToPath(appendToPath), mNotifyFileChange(notifyFileChange) {

        }

        virtual void Execute() override;
        
    protected:
        std::shared_ptr<F_U8[]> mBuffer;
        PHYSFS_uint64 mBufferLength;
        void (*mDeleteCallback)(void*);
        std::string mNewDir;
        std::string mMountPoint;
        bool mAppendToPath;
        bool mNotifyFileChange;
    };
}