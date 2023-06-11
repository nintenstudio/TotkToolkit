#pragma once

#include <TotkToolkit/IO/Streams/Physfs/PhysfsBasic.h>
#include <memory>

namespace TotkToolkit::IO {
	class Editor {
	public:
		virtual bool Parse(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) = 0;
		virtual bool Serialize(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) = 0;
	};
}