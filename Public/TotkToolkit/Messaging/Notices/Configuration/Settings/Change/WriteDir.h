#pragma once

#include <TotkToolkit/Messaging/Notice.h>

#include <string>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	class WriteDir : public TotkToolkit::Messaging::Notice {
	public:
		WriteDir(std::string oldWriteDir, std::string newWriteDir);

		std::string mOldWriteDir;
		std::string mNewWriteDir;
	};
}