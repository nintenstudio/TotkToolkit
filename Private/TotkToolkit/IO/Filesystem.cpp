#include <TotkToolkit/IO/Filesystem.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>
#include <TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h>
#include <TotkToolkit/IO/Streams/Physfs/PhysfsBasic.h>
#include <TotkToolkit/IO/Streams/File/FileBasic.h>
#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <archiver_sarc.h>
#include <physfs.h>
#include <filesystem>
#include <vector>
#include <regex>
#include <iostream>

struct SearchFilenamesByRegexCallbackData {
	SearchFilenamesByRegexCallbackData(std::string regex, std::shared_ptr<std::atomic<bool>> continueCondition) : mRegex(regex), mContinueCondition(continueCondition), mRetPaths() {

	}

	std::string mRegex;
	std::shared_ptr<std::atomic<bool>> mContinueCondition;
	std::vector<std::string> mRetPaths;
};

PHYSFS_EnumerateCallbackResult searchFilenamesByRegexCallback(void *data, const char *origdir, const char *fname) {
	SearchFilenamesByRegexCallbackData* callbackData = reinterpret_cast<SearchFilenamesByRegexCallbackData*>(data);
	
	if (!*callbackData->mContinueCondition)
		return PHYSFS_ENUM_STOP;
	
	std::string filePath = (std::filesystem::path(origdir) / std::filesystem::path(fname)).generic_string().c_str();

	std::regex regex(callbackData->mRegex.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);

	if (std::string(fname).ends_with(".pack.zs"))
		callbackData->mRetPaths.push_back(filePath);

	if (std::regex_search(fname, regex)) {
		callbackData->mRetPaths.push_back(filePath);
	}

	if (PHYSFS_isDirectory(filePath.c_str())) {
		PHYSFS_enumerate(filePath.c_str(), searchFilenamesByRegexCallback, callbackData);
	}

	return PHYSFS_EnumerateCallbackResult::PHYSFS_ENUM_OK;
}

struct SearchFilenamesByExtensionCallbackData {
	SearchFilenamesByExtensionCallbackData(std::string extension, std::shared_ptr<std::atomic<bool>> continueCondition) : mExtension(extension), mContinueCondition(continueCondition), mRetPaths() {

	}

	std::string mExtension;
	std::shared_ptr<std::atomic<bool>> mContinueCondition;
	std::vector<std::string> mRetPaths;
};

PHYSFS_EnumerateCallbackResult searchFilenamesByExtensionCallback(void *data, const char *origdir, const char *fname) {
	SearchFilenamesByExtensionCallbackData* callbackData = reinterpret_cast<SearchFilenamesByExtensionCallbackData*>(data);

	if (!*callbackData->mContinueCondition)
		return PHYSFS_ENUM_STOP;

	std::string filePath = (std::filesystem::path(origdir) / std::filesystem::path(fname)).generic_string().c_str();

	if (std::string(fname).ends_with(callbackData->mExtension))
		callbackData->mRetPaths.push_back(filePath);

	if (PHYSFS_isDirectory(filePath.c_str())) {
		PHYSFS_enumerate(filePath.c_str(), searchFilenamesByExtensionCallback, callbackData);

		if (!*callbackData->mContinueCondition)
			return PHYSFS_ENUM_STOP;
	}

	return PHYSFS_EnumerateCallbackResult::PHYSFS_ENUM_OK;
}

namespace TotkToolkit::IO {
	void Filesystem::Init() {
		PHYSFS_init("");
		PHYSFS_registerArchiver(&archiver_sarc_default);
		Formats::Resources::ZSTD::ZSTDBackend::Init();
		TotkToolkit::Messaging::NoticeBoard::AddReceiver(&sExternalReceiver);
	}

	void Filesystem::Mount(std::string path, std::string mountPoint) {
		if (path.ends_with(".zs")) {
			std::shared_ptr<Formats::IO::BinaryIOStreamBasic> readStream = std::make_shared<TotkToolkit::IO::Streams::File::FileBasic>(path);
			std::shared_ptr<Formats::IO::BinaryIOStreamBasic> decompressed = Formats::Resources::ZSTD::ZSTDBackend::Decompress(readStream);
			std::shared_ptr<F_U8[]> decompressedBuffer = decompressed->GetBuffer();
			F_UT decompressedBufferLength = decompressed->GetBufferLength();
			if (PHYSFS_mountMemory(decompressedBuffer.get(), decompressedBufferLength, nullptr, path.c_str(), mountPoint.c_str(), true))
				TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
		}
		else if (PHYSFS_mount(path.c_str(), mountPoint.c_str(), true))
			TotkToolkit::Messaging::NoticeBoard::AddNotice(std::make_shared<TotkToolkit::Messaging::Notices::IO::Filesystem::FilesChange>());
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
	std::string Filesystem::GetRealDir(std::string filePath) {
		return PHYSFS_getRealDir(filePath.c_str());
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
	std::vector<std::string> Filesystem::SearchFilenamesByRegex(std::string dir, std::string regex, std::shared_ptr<std::atomic<bool>> continueCondition) {
		SearchFilenamesByRegexCallbackData callbackRes(regex, continueCondition);

		PHYSFS_enumerate(dir.c_str(), searchFilenamesByRegexCallback, &callbackRes);

		return callbackRes.mRetPaths;
	}
	std::vector<std::string> Filesystem::SearchFilenamesByExtension(std::string dir, std::string extension, std::shared_ptr<std::atomic<bool>> continueCondition) {
		SearchFilenamesByExtensionCallbackData callbackRes(extension, continueCondition);

		PHYSFS_enumerate(dir.c_str(), searchFilenamesByExtensionCallback, &callbackRes);

		return callbackRes.mRetPaths;
	}

	TotkToolkit::Messaging::ExternalReceivers::IO::Filesystem Filesystem::sExternalReceiver;
}