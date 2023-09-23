#pragma once

#include <Formats/IO/Stream.h>

#include <Formats/IO/EndianReader.h>
#include <Formats/IO/Endianness.h>
#include <physfs.h>
#include <vector>

namespace TotkToolkit::IO::Streams::Physfs::EndianReaders {
	class Big;
	class Little;
}

#define TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(type, name) virtual type Read##name() override {\
		type res;\
		mEndianReader->ReadBytesWithEndian(&res, sizeof(type));\
		return res;\
	}
#define TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(type, name) virtual void Write##name(type value) override {\
		mEndianReader->WriteBytesWithEndian(&value, sizeof(type));\
	}

namespace TotkToolkit::IO::Streams::Physfs {
	class Physfs : public Formats::IO::Stream {
	public:
		Physfs(PHYSFS_File* file);

		virtual void Seek(std::streampos pos) override;
		virtual void PushSeek(std::streampos pos) override;
		virtual std::streampos PopSeek() override;
		virtual std::streampos GetSeek() override;
		virtual void AlignSeek(std::streampos alignment) override;

		virtual std::string ReadZeroTerminatedString(F_U32 allocation = FORMATS_IO_STREAM_READ_STRING_DEFAULTALLOCATION) override;
		virtual void WriteZeroTerminatedString(std::string value) override;

		virtual void SetEndianness(Formats::IO::Endianness endianness) override;

		virtual F_U8 ReadU8() override {
			F_U8 res;
			PHYSFS_readBytes(mFile, &res, 1);
			return res;
		}
		virtual F_S8 ReadS8() override {
			F_S8 res;
			PHYSFS_readBytes(mFile, &res, 1);
			return res;
		}
		virtual void WriteU8(F_U8 value) override {
			PHYSFS_writeBytes(mFile, &value, 1);
		}
		virtual void WriteS8(F_S8 value) override {
			PHYSFS_writeBytes(mFile, &value, 1);
		}

		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_U16, U16)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_U24, U24)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_U32, U32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_U64, U64)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_S16, S16)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_S24, S24)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_S32, S32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_S64, S64)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_F32, F32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ(F_F64, F64)

		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_U16, U16)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_U24, U24)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_U32, U32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_U64, U64)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_S16, S16)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_S24, S24)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_S32, S32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_S64, S64)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_F32, F32)
		TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE(F_F64, F64)

		virtual void ReadBytes(void* out, F_U32 size) override;
		virtual void WriteBytes(const void* in, F_U32 size) override;

		virtual std::shared_ptr<F_U8[]> GetBuffer() override;
		virtual F_UT GetBufferLength() override;

	protected:
		std::shared_ptr<Formats::IO::EndianReader> mEndianReader;

		PHYSFS_File* mFile;
		std::vector<std::streampos> mSeekStack;

		friend class TotkToolkit::IO::Streams::Physfs::EndianReaders::Little;
		friend class TotkToolkit::IO::Streams::Physfs::EndianReaders::Big;
	};
}

#undef TOTKTOOLKIT_IO_STREAMS_PHYSFS_READ
#undef TOTKTOOLKIT_IO_STREAMS_PHYSFS_WRITE