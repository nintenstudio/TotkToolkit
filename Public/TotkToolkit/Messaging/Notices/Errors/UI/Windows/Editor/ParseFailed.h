#pragma once

#include <TotkToolkit/Messaging/Notices/Error.h>

#include <string>

namespace TotkToolkit::Messaging::Notices::Errors::UI::Windows::Editor {
	class ParseFailed : public TotkToolkit::Messaging::Notices::Error {
	public:
		ParseFailed(std::string filepath);
	};
}