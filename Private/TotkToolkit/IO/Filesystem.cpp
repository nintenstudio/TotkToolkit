#include <TotkToolkit/IO/Filesystem.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <TotkToolkit/IO/Streams/Physfs/PhysfsBasic.h>
#include <archiver_sarc.h>
#include <physfs.h>
#include <filesystem>
#include <vector>
#include <regex>

struct SearchFilenamesCallbackData {
	SearchFilenamesCallbackData(std::string regex) : mRegex(regex), mRetPaths() {

	}

	std::string mRegex;
	std::vector<std::string> mRetPaths;
};

PHYSFS_EnumerateCallbackResult searchFilenamesCallback(void *data, const char *origdir, const char *fname) {
	SearchFilenamesCallbackData* callbackData = reinterpret_cast<SearchFilenamesCallbackData*>(data);

	std::regex regex(callbackData->mRegex, std::regex_constants::ECMAScript | std::regex_constants::icase);

	if (std::regex_search(fname, regex)) {
		callbackData->mRetPaths.push_back(std::filesystem::path(origdir) / std::filesystem::path(fname));
	}

	return PHYSFS_EnumerateCallbackResult::PHYSFS_ENUM_OK;
}

namespace TotkToolkit::IO {
	void Filesystem::Init() {
		PHYSFS_init("");
		PHYSFS_registerArchiver(&archiver_sarc_default);
		TotkToolkit::Messaging::NoticeBoard::AddReceiver(&sExternalReceiver);
	}

	void Filesystem::Mount(std::string path) {
		if(PHYSFS_mount(path.c_str(), "", true)) {
			//std::vector<std::string> packs = SearchFilenames("", "*.pack");


			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
		}
	}
	void Filesystem::Unmount(std::string path) {
		if (PHYSFS_unmount(path.c_str()))
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
	}
	void Filesystem::SetWriteDir(std::string dir) {
		PHYSFS_setWriteDir(dir.c_str());
	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> Filesystem::GetReadStream(std::string filepath) {
		PHYSFS_File* file = PHYSFS_openRead(filepath.c_str());
		return std::make_shared<TotkToolkit::IO::Streams::Physfs::PhysfsBasic>(file);
	}
	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> Filesystem::GetWriteStream(std::string filepath) {
		PHYSFS_File* file = PHYSFS_openWrite(filepath.c_str());
		return std::make_shared<TotkToolkit::IO::Streams::Physfs::PhysfsBasic>(file);
	}

	std::vector<std::string> Filesystem::EnumerateFiles(std::string path) {
		std::vector<std::string> res;

		char** files = PHYSFS_enumerateFiles(path.c_str());

		char* currentFile;
		for (F_U32 i = 0; currentFile = files[i], currentFile != nullptr; i++) {
			if (!PHYSFS_isDirectory((std::filesystem::path(path) / std::filesystem::path(currentFile)).generic_string().c_str()))
				res.push_back(currentFile);
		}

		return res;
	}
	std::vector<std::string> Filesystem::EnumerateDirectories(std::string path) {
		std::vector<std::string> res;

		char** files = PHYSFS_enumerateFiles(path.c_str());

		char* currentFile;
		for (F_U32 i = 0; currentFile = files[i], currentFile != nullptr; i++) {
			if (PHYSFS_isDirectory((std::filesystem::path(path) / std::filesystem::path(currentFile)).generic_string().c_str()))
				res.push_back(currentFile);
		}

		return res;
	}
	std::vector<std::string> Filesystem::SearchFilenames(std::string dir, std::string regex) {
		SearchFilenamesCallbackData callbackRes(regex);

		PHYSFS_enumerate(dir.c_str(), searchFilenamesCallback, &callbackRes);

		return callbackRes.mRetPaths;
	}

	TotkToolkit::Messaging::ExternalReceivers::IO::Filesystem Filesystem::sExternalReceiver;
}