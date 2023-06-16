#pragma once

#include <TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h>
#include <physfs.h>
#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>
#include <vector>

namespace TotkToolkit::IO {
	class Filesystem {
	public:
		static void Init();

		static void MountDir(std::string dir);
		static void UnmountDir(std::string dir);

		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetReadStream(std::string filepath);
		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetWriteStream(std::string filepath);

		static std::vector<std::string> EnumerateFiles(std::string path);
		static std::vector<std::string> EnumerateDirectories(std::string path);

	protected:
		static TotkToolkit::Messaging::ExternalReceivers::IO::Filesystem sExternalReceiver;
	};
}