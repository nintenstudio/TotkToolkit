#pragma once

#include <TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h>
#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>
#include <vector>
#include <string>
#include <atomic>

namespace TotkToolkit::IO {
	class Filesystem {
	public:
		static void Init();

		/// @brief Should be called at least once on new threads that use filesystem.
		static void InitThread();
		static void SyncThread();

		static void Mount(std::string path, std::string mountPoint);
		static void MountStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream, std::string filename, std::string mountPoint);
		static void Unmount(std::string path);
		static void SetWriteDir(std::string dir);

		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetReadStream(std::string filepath);
		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> GetWriteStream(std::string filepath);
		static std::string GetRealDir(std::string path);

		static std::vector<std::string> EnumerateFiles(std::string path);
		static std::vector<std::string> EnumerateDirectories(std::string path);
		static std::vector<std::string> SearchFilenamesByRegex(std::string dir, std::string regex, std::shared_ptr<std::atomic<bool>> continueCondition = std::make_shared<std::atomic<bool>>(true));
		static std::vector<std::string> SearchFilenamesByExtension(std::string dir, std::string extension, std::shared_ptr<std::atomic<bool>> continueCondition = std::make_shared<std::atomic<bool>>(true));

	protected:
		static TotkToolkit::Messaging::ExternalReceivers::IO::Filesystem sExternalReceiver;
	};
}