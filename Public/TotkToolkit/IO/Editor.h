#pragma once

#include <Formats/IO/BinaryIOStream.h>

namespace TotkToolkit::IO {
	class Editor {
	public:
		virtual bool Parse(Formats::IO::BinaryIOStream& stream) = 0;
		virtual bool Serialize(Formats::IO::BinaryIOStream& stream) = 0;
	};
}