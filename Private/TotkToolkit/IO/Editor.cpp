#include <TotkToolkit/IO/Editor.h>

namespace TotkToolkit::IO {
	Editor::Editor(TotkToolkit::IO::FileHandle fileHandle) : mFileHandle(fileHandle) {

	}
	Editor::Editor(std::shared_ptr<Formats::Resource> resource) : mFileHandle() {
		// It's not currently valuable to store a base-type resource here.
		// Right now this constructor does nothing but open up a new mode of operation.
	}
}