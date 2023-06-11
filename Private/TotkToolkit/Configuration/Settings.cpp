#include <TotkToolkit/Configuration/Settings.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/RomfsDir.h>

namespace TotkToolkit::Configuration {
	std::string Settings::GetRomfsDir() {
		return sRomfsDir;
	}
	void Settings::SetRomfsDir(std::string romfsDir) {
		std::string oldRomfsDir = sRomfsDir;
		sRomfsDir = romfsDir;

		if (oldRomfsDir != romfsDir)
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_unique<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::RomfsDir>(oldRomfsDir, romfsDir));
	}

	std::string Settings::sRomfsDir;
}