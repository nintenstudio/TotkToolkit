#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/BfresDir.h>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	BfresDir::BfresDir(std::string oldBfresDir, std::string newBfresDir) : 
		mOldBfresDir(oldBfresDir), 
		mNewBfresDir(newBfresDir), 
		TotkToolkit::Messaging::Notice::Notice(TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_BFRESDIR)
	{
	}
}