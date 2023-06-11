#pragma once

#include <TotkToolkit/Messaging/NoticeType.h>

namespace TotkToolkit::Messaging {
	class Notice {
	public:
		Notice(TotkToolkit::Messaging::NoticeType noticeType);

		TotkToolkit::Messaging::NoticeType mNoticeType;
	};
}