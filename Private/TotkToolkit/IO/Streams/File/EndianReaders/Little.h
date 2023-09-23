#pragma once

#include <Formats/IO/EndianReader.h>

#include <TotkToolkit/IO/Streams/File/File.h>
#include <algorithm>

namespace TotkToolkit::IO::Streams::File::EndianReaders {
	class Little : public Formats::IO::EndianReader {
	public:
		Little(Formats::IO::Stream* parentStream) : Formats::IO::EndianReader::EndianReader(parentStream) {

		}
		
		virtual void ReadBytesWithEndian(void* out, F_UT length) override {
			static_cast<TotkToolkit::IO::Streams::File::File*>(mParentStream)->mFile->read(reinterpret_cast<F_S8*>(out), length);
#if (FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
		}
		virtual void WriteBytesWithEndian(void* in, F_U64 length) override {
#if (FORMATS_BIGENDIAN)
			F_S8* reversed = new F_S8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
			static_cast<TotkToolkit::IO::Streams::File::File*>(mParentStream)->mFile->write(reversed, length);
#else
			static_cast<TotkToolkit::IO::Streams::File::File*>(mParentStream)->mFile->write(reinterpret_cast<F_S8*>(in), length);
#endif
		}
	};
}