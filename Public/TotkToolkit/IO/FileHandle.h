#pragma once

#include <Formats/IO/Stream.h>
#include <memory>
#include <string>

namespace TotkToolkit::IO {
	class FileHandle {
	public:
		FileHandle();
		FileHandle(std::string path);

		bool IsNull();

		std::shared_ptr<Formats::IO::Stream> GetReadStream();
		std::shared_ptr<Formats::IO::Stream> GetWriteStream();

	protected:
		std::string mPath;
	};
}