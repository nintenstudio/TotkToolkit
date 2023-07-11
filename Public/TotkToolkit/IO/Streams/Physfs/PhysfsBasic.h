#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>

#include <physfs.h>

namespace TotkToolkit::IO::Streams::Physfs {
	class PhysfsBasic : public Formats::IO::BinaryIOStreamBasic {
	public:
		PhysfsBasic(PHYSFS_File* file);

		virtual std::shared_ptr<Formats::IO::BinaryIOStream> Factory(Formats::IO::Endianness endianness) override;

		virtual void ReadBytes(void* out, F_U32 length) override;
		virtual void WriteBytes(const void* in, F_U32 length) override;

		virtual std::shared_ptr<F_U8> GetBuffer() override;
		virtual F_UT GetBufferLength() override;

	protected:
		PHYSFS_File* mFile;
	};
}