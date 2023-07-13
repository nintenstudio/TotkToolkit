#include <TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.h>
#include <TotkToolkit/Messaging/Notices/Configuration/Settings/Change/WriteDir.h>
#include <Formats/Resources/ZSTD/ZSTDBackend.h>

namespace TotkToolkit::Messaging::ExternalReceivers::IO {
	void Filesystem::HandleNotice(std::shared_ptr<TotkToolkit::Messaging::Notice> notice) {
		switch (notice->mType) {
			case TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_DUMPDIR: {
					std::shared_ptr<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::DumpDir> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::DumpDir>(notice);

					TotkToolkit::IO::Filesystem::Unmount(castNotice->mOldDumpDir);
					TotkToolkit::IO::Filesystem::Mount(castNotice->mNewDumpDir, "");

					// Initialize ZSTD dictionaries
					TotkToolkit::IO::Filesystem::Mount(TotkToolkit::IO::Filesystem::GetRealDir("romfs/Pack/ZsDic.pack.zs"), "romfs");
					//Formats::Resources::ZSTD::ZSTDBackend::AddDict();
					return;
				}
			case TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_WRITEDIR: {
					std::shared_ptr<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::WriteDir> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::WriteDir>(notice);

					TotkToolkit::IO::Filesystem::SetWriteDir(castNotice->mNewWriteDir);
					return;
				}
			default:
				return;
		}
	}
}