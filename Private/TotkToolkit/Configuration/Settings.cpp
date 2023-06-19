#include <TotkToolkit/Configuration/Settings.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/WriteDir.h>

namespace TotkToolkit::Configuration {
	std::string Settings::GetDumpDir() {
		return sDumpDir;
	}
	void Settings::SetDumpDir(std::string dumpDir) {
		std::string oldDumpDir = sDumpDir;
		sDumpDir = dumpDir;

		if (oldDumpDir != dumpDir)
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_unique<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::DumpDir>(oldDumpDir, dumpDir));
	}

	std::string Settings::GetWriteDir() {
		return sWriteDir;
	}
	void Settings::SetWriteDir(std::string writeDir) {
		std::string oldWriteDir = sWriteDir;
		sWriteDir = writeDir;

		if (oldWriteDir != writeDir)
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_unique<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::WriteDir>(oldWriteDir, writeDir));
	}

	std::string Settings::sDumpDir;
	std::string Settings::sWriteDir;
}