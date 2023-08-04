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

					TotkToolkit::IO::Filesystem::InitThread();
					TotkToolkit::IO::Filesystem::SyncThread();
					TotkToolkit::IO::Filesystem::Unmount(castNotice->mOldDumpDir);
					TotkToolkit::IO::Filesystem::Mount(castNotice->mNewDumpDir, "");

					// Initialize ZSTD dictionaries
					std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZsDicPack = TotkToolkit::IO::Filesystem::GetReadStream("romfs/Pack/ZsDic.pack.zs");
					if (ZsDicPack != nullptr) {
						TotkToolkit::IO::Filesystem::MountStream(ZsDicPack, "ZsDic.pack.zs", "romfs");

						std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZsZsdic = TotkToolkit::IO::Filesystem::GetReadStream("romfs/zs.zsdic");
						if (ZsZsdic != nullptr)
							Formats::Resources::ZSTD::ZSTDBackend::AddDict(ZsZsdic);
						std::shared_ptr<Formats::IO::BinaryIOStreamBasic> BcettBymlZsdic = TotkToolkit::IO::Filesystem::GetReadStream("romfs/bcett.byml.zsdic");
						if (BcettBymlZsdic != nullptr)
							Formats::Resources::ZSTD::ZSTDBackend::AddDict(BcettBymlZsdic);
						std::shared_ptr<Formats::IO::BinaryIOStreamBasic> PackZsDic = TotkToolkit::IO::Filesystem::GetReadStream("romfs/pack.zsdic");
						if (PackZsDic != nullptr)
							Formats::Resources::ZSTD::ZSTDBackend::AddDict(PackZsDic);
					}
					return;
				}
			case TotkToolkit::Messaging::NoticeType::CONFIGURATION_SETTINGS_CHANGE_WRITEDIR: {
					std::shared_ptr<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::WriteDir> castNotice = std::static_pointer_cast<TotkToolkit::Messaging::Notices::Configuration::Settings::Change::WriteDir>(notice);

					TotkToolkit::IO::Filesystem::InitThread();
					TotkToolkit::IO::Filesystem::SyncThread();
					TotkToolkit::IO::Filesystem::SetWriteDir(castNotice->mNewWriteDir);
					return;
				}
			default:
				return;
		}
	}
}