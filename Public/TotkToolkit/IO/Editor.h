#pragma once

#include <TotkToolkit/IO/FileHandle.h>
#include <Formats/Resource.h>
#include <memory>

namespace TotkToolkit::IO {
	class Editor {
	public:
		Editor(TotkToolkit::IO::FileHandle fileHandle);
		Editor(std::shared_ptr<Formats::Resource> resource);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;

	protected:
		TotkToolkit::IO::FileHandle mFileHandle;
	};
}