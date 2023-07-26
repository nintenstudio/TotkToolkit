#pragma once

#include <TotkToolkit/Messaging/NoticeBoard.h>

#include <chrono>

namespace TotkToolkit::Messaging {
	void NoticeBoard::AddNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		std::unique_lock<std::shared_mutex> lock(sReceiverExecutionFuturesMutex);
		for (std::vector<std::future<void>>::iterator it = sReceiverExecutionFutures.begin(); it < sReceiverExecutionFutures.end();) {
			if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				it = sReceiverExecutionFutures.erase(it);
			it++;
		}
		for (TotkToolkit::Messaging::Receiver* receiver : sReceivers) {
			sReceiverExecutionFutures.push_back(std::async(std::launch::async, [receiver, notice]() -> void {receiver->HandleNotice(notice);}));
		}
	}

	void NoticeBoard::AddReceiver(TotkToolkit::Messaging::Receiver* receiver) {
		std::unique_lock<std::shared_mutex> lock(sReceiversMutex);
		sReceivers.push_back(receiver);
	}

	std::vector<TotkToolkit::Messaging::Receiver*> NoticeBoard::sReceivers;
	std::shared_mutex NoticeBoard::sReceiversMutex;

	std::vector<std::future<void>> NoticeBoard::sReceiverExecutionFutures;
	std::shared_mutex NoticeBoard::sReceiverExecutionFuturesMutex;
}