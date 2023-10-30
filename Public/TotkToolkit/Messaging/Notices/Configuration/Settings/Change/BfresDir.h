#pragma once

#include <TotkToolkit/Messaging/Notice.h>

#include <string>

namespace TotkToolkit::Messaging::Notices::Configuration::Settings::Change {
	class BfresDir : public TotkToolkit::Messaging::Notice {
	public:
		BfresDir(std::string oldBfresDir, std::string newBfresDir);

		std::string mOldBfresDir;
		std::string mNewBfresDir;
	};
}