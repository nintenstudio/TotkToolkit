#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.h>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	DumpDir::DumpDir(std::string oldDumpDir, std::string newDumpDir) : 
		mOldDumpDir(oldDumpDir), 
		mNewDumpDir(newDumpDir), 
		TotkToolkit::Messaging::Notice::Notice(TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_DUMPDIR)
	{
	}
}