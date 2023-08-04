#pragma once

#include <TotkToolkit/IO/PHYSFSCall.h>

#include <Formats/Aliases/Primitives.h>
#include <physfs.h>
#include <string>
#include <memory>

namespace TotkToolkit::IO::PHYSFSCalls {
    class SetWriteDir : public TotkToolkit::IO::PHYSFSCall {
    public:
        SetWriteDir(std::string writeDir) : mWriteDir(writeDir) {

        }

        virtual void Execute() override;

    protected:
        std::string mWriteDir;
    };
}