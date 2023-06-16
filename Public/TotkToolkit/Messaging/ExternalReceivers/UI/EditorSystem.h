#pragma once

#include <TotkToolkit/Messaging/Receiver.h>

namespace TotkToolkit::Messaging::ExternalReceivers::UI {
	class EditorSystem : public TotkToolkit::Messaging::Receiver {
	public:
		virtual void HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) override;
	};
}