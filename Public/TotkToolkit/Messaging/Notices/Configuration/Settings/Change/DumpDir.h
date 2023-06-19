#pragma once

#include <TotkToolkit/Messaging/Notice.h>

#include <string>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	class DumpDir : public TotkToolkit::Messaging::Notice {
	public:
		DumpDir(std::string oldDumpDir, std::string newDumpDir);

		std::string mOldDumpDir;
		std::string mNewDumpDir;
	};
}