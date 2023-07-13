#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>

#include <fstream>
#include <string>
#include <memory>

namespace TotkToolkit::IO::Streams::File {
	class FileBasic : public Formats::IO::BinaryIOStreamBasic {
	public:
		FileBasic(std::string filePath);
		FileBasic(std::shared_ptr<std::fstream> file);

		virtual std::shared_ptr<Formats::IO::BinaryIOStream> Factory(Formats::IO::Endianness endianness) override;

		virtual void ReadBytes(void* out, F_U32 length) override;
		virtual void WriteBytes(const void* in, F_U32 length) override;

		virtual std::shared_ptr<F_U8[]> GetBuffer() override;
		virtual F_UT GetBufferLength() override;

	protected:
		std::shared_ptr<std::fstream> mFile;
	};
}