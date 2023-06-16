#pragma once

#include <TotkToolkit/Messaging/NoticeType.h>

namespace TotkToolkit::Messaging {
	class Notice {
	public:
		Notice(TotkToolkit::Messaging::NoticeType type);

		TotkToolkit::Messaging::NoticeType mType;
	};
}