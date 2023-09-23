#include <TotkToolkit/Messaging/ExternalReceivers/UI/ErrorSystem.h>

#include <TotkToolkit/UI/ErrorSystem.h>
#include <TotkToolkit/Messaging/Notices/Error.h>
#include <TotkToolkit/Messaging/NoticeType.h>
#include <shared_mutex>

namespace TotkToolkit::Messaging::ExternalReceivers::UI {
	void ErrorSystem::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		switch (notice->mType) {
		case TotkToolkit::Messaging::NoticeType::ERRORS_UI_WINDOWS_EDITOR_PARSEFAILED: {
			std::shared_ptr<TotkToolkit::Messaging::Notices::Error> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Error>(notice);

			std::unique_lock<std::shared_mutex> lock(TotkToolkit::UI::ErrorSystem::sMessagesMutex);
			TotkToolkit::UI::ErrorSystem::sMessages.push_back(castNotice->GetMessage());

			break;
		}
		default:
			return;
		}
	}
}