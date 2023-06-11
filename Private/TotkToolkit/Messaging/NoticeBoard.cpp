#pragma once

#include <TotkToolkit/Messaging/NoticeBoard.h>

namespace TotkToolkit::Messaging {
	void NoticeBoard::AddNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		for (TotkToolkit::Messaging::Receiver* receiver : sReceivers) {
			receiver->HandleNotice(notice);
		}
	}

	void NoticeBoard::AddReceiver(TotkToolkit::Messaging::Receiver* receiver) {
		sReceivers.push_back(receiver);
	}

	std::vector<TotkToolkit::Messaging::Receiver*> NoticeBoard::sReceivers;
}