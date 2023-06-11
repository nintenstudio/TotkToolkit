#pragma once

#include <TotkToolkit/Messaging/Notice.h>
#include <memory>

namespace TotkToolkit::Messaging {
	class Receiver {
	public:
		virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) = 0;
	};
}