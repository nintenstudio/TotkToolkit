#pragma once

#include <TotkToolkit/IO/FileHandle.h>

#include <TotkToolkit/IO/Filesystem.h>

namespace TotkToolkit::IO {
	FileHandle::FileHandle(std::string path) : mPath(path) {

	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> FileHandle::GetReadStream() {
		TotkToolkit::IO::Filesystem::InitThread();
		TotkToolkit::IO::Filesystem::SyncThread();
		return TotkToolkit::IO::Filesystem::GetReadStream(mPath);
	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> FileHandle::GetWriteStream() {
		TotkToolkit::IO::Filesystem::InitThread();
		TotkToolkit::IO::Filesystem::SyncThread();
		return TotkToolkit::IO::Filesystem::GetWriteStream(mPath);
	}
}