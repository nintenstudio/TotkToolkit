#include <TotkToolkit/Messaging/ExternalReceivers/UI/EditorSystem.h>

#include <TotkToolkit/UI/EditorSystem.h>

namespace TotkToolkit::Messaging::ExternalReceivers::UI {
	void EditorSystem::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		switch (notice->mType) {
		default:
			return;
		}
	}
}