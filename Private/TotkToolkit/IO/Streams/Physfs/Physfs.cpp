#include <TotkToolkit/IO/Streams/Physfs/Physfs.h>

#include <TotkToolkit/IO/Streams/Physfs/EndianReaders/Little.h>
#include <TotkToolkit/IO/Streams/Physfs/EndianReaders/Big.h>
#include <Formats/Aliases/Primitives.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::Physfs {
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

	void Physfs::SetEndianness(Formats::IO::Endianness endianness) {
		switch (endianness) {
            case Formats::IO::Endianness::LITTLE:
                mEndianReader = std::make_shared<TotkToolkit::IO::Streams::Physfs::EndianReaders::Little>(this);
                break;
            case Formats::IO::Endianness::BIG:
                mEndianReader = std::make_shared<TotkToolkit::IO::Streams::Physfs::EndianReaders::Big>(this);
                break;
            default:
                assert(false); // endianness is invalid!
        }
	}

	void Physfs::ReadBytes(void* out, F_U32 size) {
		PHYSFS_readBytes(mFile, out, size);
	}
	void Physfs::WriteBytes(const void* in, F_U32 size) {
		PHYSFS_writeBytes(mFile, in, size);
	}

	std::shared_ptr<F_U8[]> Physfs::GetBuffer() {
		PushSeek(0);

		F_U64 length = (F_U64)GetBufferLength();

		std::shared_ptr<F_U8[]> res = std::shared_ptr<F_U8[]>(new F_U8[length]);
		PHYSFS_readBytes(mFile, res.get(), length);
		
		return res;
	}
	F_UT Physfs::GetBufferLength() {
		return (F_UT)PHYSFS_fileLength(mFile);
	}
}