#pragma once

#include <TotkToolkit/IO/FileHandle.h>

#include <TotkToolkit/IO/Filesystem.h>

namespace TotkToolkit::IO {
	FileHandle::FileHandle() : mPath("\0") {
		// Represent a null value.
	}
	FileHandle::FileHandle(std::string path) : mPath(path) {

	}

	bool FileHandle::IsNull() {
		return mPath.compare("\0") == 0;
	}

	std::shared_ptr<Formats::IO::Stream> FileHandle::GetReadStream() {
		TotkToolkit::IO::Filesystem::InitThread();
		TotkToolkit::IO::Filesystem::SyncThread();
		return TotkToolkit::IO::Filesystem::GetReadStream(mPath);
	}

	std::shared_ptr<Formats::IO::Stream> FileHandle::GetWriteStream() {
		TotkToolkit::IO::Filesystem::InitThread();
		TotkToolkit::IO::Filesystem::SyncThread();
		return TotkToolkit::IO::Filesystem::GetWriteStream(mPath);
	}
}