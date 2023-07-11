#include <TotkToolkit/IO/Streams/Physfs/Physfs.h>

#include <TotkToolkit/IO/Streams/Physfs/Little.h>
#include <TotkToolkit/IO/Streams/Physfs/Big.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::Physfs {
	std::shared_ptr<Formats::IO::BinaryIOStream> Physfs::Factory(PHYSFS_File* file, Formats::IO::Endianness endianness) {
		assert(endianness == Formats::IO::Endianness::LITTLE || endianness == Formats::IO::Endianness::BIG);

		if (endianness == Formats::IO::Endianness::LITTLE)
			return std::make_shared<TotkToolkit::IO::Streams::Physfs::Little>(file);
		else
			return std::make_shared<TotkToolkit::IO::Streams::Physfs::Big>(file);
	}
	Physfs::Physfs(PHYSFS_File* file) : mFile(file) {

	}

	void Physfs::Seek(std::streampos pos) {
		PHYSFS_seek(mFile, pos);
	}
	void Physfs::PushSeek(std::streampos pos) {
		mSeekStack.push_back(PHYSFS_tell(mFile));

		PHYSFS_seek(mFile, pos);
	}
	std::streampos Physfs::PopSeek() {
		std::streampos res = PHYSFS_tell(mFile);

		PHYSFS_seek(mFile, mSeekStack.back());
		mSeekStack.pop_back();

		return res;
	}
	std::streampos Physfs::GetSeek() {
		return PHYSFS_tell(mFile);
	}
	void Physfs::AlignSeek(std::streampos alignment) {
		std::streampos pos = PHYSFS_tell(mFile);
		pos = (pos % alignment == 0) ? pos : alignment - (pos % alignment) + pos;
		PHYSFS_seek(mFile, pos);
	}
	std::string Physfs::ReadZeroTerminatedString(F_U32 allocation) {
		std::string res;
		res.reserve(allocation);

		char currentChar;
		while(PHYSFS_readBytes(mFile, &currentChar, 1), currentChar != '\0') {
			res += currentChar;
		}

		return res;
	}
	void Physfs::WriteZeroTerminatedString(std::string value) {
		PHYSFS_writeBytes(mFile, value.c_str(), value.size() + 1);
	}

	void Physfs::ReadBytes(void* out, F_U32 size) {
		PHYSFS_readBytes(mFile, out, size);
	}
	void Physfs::WriteBytes(const void* in, F_U32 size) {
		PHYSFS_writeBytes(mFile, in, size);
	}
}