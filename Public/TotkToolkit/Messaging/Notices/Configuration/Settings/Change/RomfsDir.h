#pragma once

#include <TotkToolkit/Messaging/Notice.h>

#include <string>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	class RomfsDir : public TotkToolkit::Messaging::Notice {
	public:
		RomfsDir(std::string oldRomfsDir, std::string newRomfsDir);

		std::string mOldRomfsDir;
		std::string mNewRomfsDir;
	};
}