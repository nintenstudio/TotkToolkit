#pragma once

#include <TotkToolkit/IO/Streams/Physfs/Physfs.h>

#include <algorithm>

namespace TotkToolkit::IO::Streams::Physfs {
	class Big : public TotkToolkit::IO::Streams::Physfs::Physfs {
	public:
		Big(PHYSFS_File* file) : TotkToolkit::IO::Streams::Physfs::Physfs(file) {

		}

	protected:
		virtual void ReadBytesWithEndian(void* out, PHYSFS_uint64 length) override {
			PHYSFS_readBytes(mFile, out, length);
#if (!FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
		}
		virtual void WriteBytesWithEndian(void* in, PHYSFS_uint64 length) override {
#if (!FORMATS_BIGENDIAN)
			F_U8* reversed = new F_U8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
			PHYSFS_writeBytes(mFile, reversed, length);
#else
			PHYSFS_writeBytes(&mFile, in, length);
#endif
		}
	};
}