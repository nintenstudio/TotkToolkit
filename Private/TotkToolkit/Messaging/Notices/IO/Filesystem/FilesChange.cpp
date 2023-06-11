#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>

namespace TotkToolkit::Messaging::Notices::IO::Filesystem {
	FilesChange::FilesChange() :
		TotkToolkit::Messaging::Notice::Notice(TotkToolkit::Messaging::NoticeType::IO_FILESYSTEM_FILESCHANGE)
	{
	}
}