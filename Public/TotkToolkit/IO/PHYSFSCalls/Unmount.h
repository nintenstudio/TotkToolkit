#pragma once

#include <TotkToolkit/IO/PHYSFSCall.h>

#include <string>

namespace TotkToolkit::IO::PHYSFSCalls {
    class Unmount : public TotkToolkit::IO::PHYSFSCall {
    public:
        Unmount(std::string path) : mPath(path) {

        }

        virtual void Execute() override;

    protected:
        std::string mPath;
    };
}