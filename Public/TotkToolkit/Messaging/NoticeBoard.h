#pragma once

#include <TotkToolkit/Messaging/Receiver.h>
#include <TotkToolkit/Messaging/Notice.h>
#include <vector>
#include <future>
#include <shared_mutex>
#include <memory>

namespace TotkToolkit::Messaging {
	class NoticeBoard {
	public:
		static void AddNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice);
		static void AddReceiver(TotkToolkit::Messaging::Receiver* receiver);

	protected:
		static std::vector<TotkToolkit::Messaging::Receiver*> sReceivers;
		static std::shared_mutex sReceiversMutex;

	private:
		static std::vector<std::future<void>> sReceiverExecutionFutures;
		static std::shared_mutex sReceiverExecutionFuturesMutex;
	};
}