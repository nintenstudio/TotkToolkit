#pragma once

#include <iostream>

namespace TotkToolkit::IO {
	class Editor {
	public:
		virtual bool Parse(std::iostream* stream) = 0;
		virtual bool Serialize(std::iostream* stream) = 0;
	};
}