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
}