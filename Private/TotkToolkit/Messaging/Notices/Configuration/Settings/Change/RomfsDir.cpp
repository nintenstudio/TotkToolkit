#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/RomfsDir.h>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	RomfsDir::RomfsDir(std::string oldRomfsDir, std::string newRomfsDir) : 
		mOldRomfsDir(oldRomfsDir), 
		mNewRomfsDir(newRomfsDir), 
		TotkToolkit::Messaging::Notice::Notice(TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_ROMFSDIR)
	{
	}
}