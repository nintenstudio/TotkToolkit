#pragma once

#include <TotkToolkit/IO/Streams/File/File.h>

#include <algorithm>

namespace TotkToolkit::IO::Streams::File {
	class Big : public TotkToolkit::IO::Streams::File::File {
	public:
		Big(std::string filePath) : TotkToolkit::IO::Streams::File::File(filePath) {

		}
		Big(std::shared_ptr<std::fstream> file) : TotkToolkit::IO::Streams::File::File(file) {

		}

	protected:
		virtual void ReadBytesWithEndian(void* out, F_U64 length) override {
			mFile->read(reinterpret_cast<F_S8*>(out), length);
#if (!FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
		}
		virtual void WriteBytesWithEndian(void* in, F_U64 length) override {
#if (!FORMATS_BIGENDIAN)
			F_S8* reversed = new F_S8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
			mFile->write(reversed, length);
#else
			mFile->write(reinterpret_cast<F_S8*>(in), length);
#endif
		}
	};
}