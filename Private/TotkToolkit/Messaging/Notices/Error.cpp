#include <TotkToolkit/Messaging/Notices/Error.h>

namespace TotkToolkit::Messaging::Notices {
    Error::Error(TotkToolkit::Messaging::NoticeType noticeType, std::string message) : TotkToolkit::Messaging::Notice(noticeType), mMessage(message) {

    }

    std::string Error::GetMessage() {
        return mMessage;
    }
}