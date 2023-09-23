#pragma once

#include <TotkToolkit/Messaging/Notice.h>
#include <string>

namespace TotkToolkit::Messaging::Notices {
    class Error : public TotkToolkit::Messaging::Notice {
    public:
        std::string GetMessage();

    protected:
        Error(TotkToolkit::Messaging::NoticeType noticeType, std::string message);

        std::string mMessage;
    };
}