#pragma once

#include <TotkToolkit/Messaging/Notice.h>

namespace TotkToolkit::Messaging::Notices::IO::Filesystem {
	class FilesChange : public TotkToolkit::Messaging::Notice {
	public:
		FilesChange();
	};
}