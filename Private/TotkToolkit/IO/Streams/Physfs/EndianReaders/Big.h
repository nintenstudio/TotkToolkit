#pragma once

#include <Formats/IO/EndianReader.h>

#include <TotkToolkit/IO/Streams/Physfs/Physfs.h>
#include <physfs.h>
#include <algorithm>

namespace TotkToolkit::IO::Streams::Physfs::EndianReaders {
	class Big : public Formats::IO::EndianReader {
	public:
		Big(Formats::IO::Stream* parentStream) : Formats::IO::EndianReader::EndianReader(parentStream) {

		}

		virtual void ReadBytesWithEndian(void* out, F_UT length) override {
			PHYSFS_readBytes(static_cast<TotkToolkit::IO::Streams::Physfs::Physfs*>(mParentStream)->mFile, out, length);
#if (!FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
		}
		virtual void WriteBytesWithEndian(void* in, F_UT length) override {
#if (!FORMATS_BIGENDIAN)
			F_U8* reversed = new F_U8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
			PHYSFS_writeBytes(static_cast<TotkToolkit::IO::Streams::Physfs::Physfs*>(mParentStream)->mFile, reversed, length);
#else
			PHYSFS_writeBytes(&static_cast<TotkToolkit::IO::Streams::Physfs::Physfs*>(mParentStream)->mFile, in, length);
#endif
		}
	};
}