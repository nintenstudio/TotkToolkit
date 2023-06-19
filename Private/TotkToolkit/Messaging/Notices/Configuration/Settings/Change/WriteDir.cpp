#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/WriteDir.h>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	WriteDir::WriteDir(std::string oldWriteDir, std::string newWriteDir) : 
		mOldWriteDir(oldWriteDir), 
		mNewWriteDir(newWriteDir), 
		TotkToolkit::Messaging::Notice::Notice(TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_WRITEDIR)
	{
	}
}