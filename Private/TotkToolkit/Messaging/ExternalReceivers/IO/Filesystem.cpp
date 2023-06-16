#include <TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/RomfsDir.h>

namespace TotkToolkit::Messaging::ExternalReceivers::IO {
	void Filesystem::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		switch (notice->mType) {
			case TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_ROMFSDIR: {
				std::shared_ptr<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::RomfsDir> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::RomfsDir>(notice);

				TotkToolkit::IO::Filesystem::UnmountDir(castNotice->mOldRomfsDir);
				TotkToolkit::IO::Filesystem::MountDir(castNotice->mNewRomfsDir);
				return;
				}
			default:
				return;
		}
	}
}