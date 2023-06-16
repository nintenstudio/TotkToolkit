#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>
#include <string>

namespace TotkToolkit::IO {
	class FileHandle {
	public:
		FileHandle(std::string path);

		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetReadStream();
		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetWriteStream();

	protected:
		std::string mPath;
	};
}