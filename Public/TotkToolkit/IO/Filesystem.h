#pragma once

#include <TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h>
#include <physfs.h>
#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>
#include <vector>
#include <string>

namespace TotkToolkit::IO {
	class Filesystem {
	public:
		static void Init();

		static void Mount(std::string path);
		static void Unmount(std::string path);
		static void SetWriteDir(std::string dir);

		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetReadStream(std::string filepath);
		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetWriteStream(std::string filepath);

		static std::vector<std::string> EnumerateFiles(std::string path);
		static std::vector<std::string> EnumerateDirectories(std::string path);
		static std::vector<std::string> SearchFilenames(std::string dir, std::string regex);

	protected:
		static TotkToolkit::Messaging::ExternalReceivers::IO::Filesystem sExternalReceiver;
	};
}