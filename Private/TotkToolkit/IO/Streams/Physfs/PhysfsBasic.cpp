#include <TotkToolkit/IO/Streams/Physfs/PhysfsBasic.h>

#include <TotkToolkit/IO/Streams/Physfs/Little.h>
#include <TotkToolkit/IO/Streams/Physfs/Big.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::Physfs {
	PhysfsBasic::PhysfsBasic(PHYSFS_File* file) : mFile(file) {

	}

	std::shared_ptr<Formats::IO::BinaryIOStream> PhysfsBasic::Factory(Formats::IO::Endianness endianness) {
		assert(endianness == Formats::IO::Endianness::LITTLE || endianness == Formats::IO::Endianness::BIG);

		if (endianness == Formats::IO::Endianness::LITTLE) {
			return std::make_shared<TotkToolkit::IO::Streams::Physfs::Little>(mFile);
		}
		else {
			return std::make_shared<TotkToolkit::IO::Streams::Physfs::Big>(mFile);
		}
	}

	void PhysfsBasic::ReadBytes(void* out, F_U32 length) {
		PHYSFS_readBytes(mFile, out, length);
	}
	void PhysfsBasic::WriteBytes(const void* in, F_U32 length) {
		PHYSFS_writeBytes(mFile, in, length);
	}

	std::shared_ptr<F_U8> PhysfsBasic::GetBuffer() {
		PHYSFS_sint64 length = PHYSFS_fileLength(mFile);
		assert(length != -1); // Not sure what we should do in this case..

		F_U8* buffer = new F_U8[length];
		PHYSFS_seek(mFile, 0);
		PHYSFS_readBytes(mFile, buffer, length);

		return std::shared_ptr<F_U8>(buffer);
	}
	F_UT PhysfsBasic::GetBufferLength() {
		return PHYSFS_fileLength(mFile);
	}
}