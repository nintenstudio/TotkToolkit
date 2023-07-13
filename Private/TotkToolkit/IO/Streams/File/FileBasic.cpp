#include <TotkToolkit/IO/Streams/File/FileBasic.h>

#include <TotkToolkit/IO/Streams/File/Little.h>
#include <TotkToolkit/IO/Streams/File/Big.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::File {
	FileBasic::FileBasic(std::string filePath) : mFile(new std::fstream(filePath, std::ios::in | std::ios::out | std::ios::binary)) {

	}
	FileBasic::FileBasic(std::shared_ptr<std::fstream> file) : mFile(file) {

	}

	std::shared_ptr<Formats::IO::BinaryIOStream> FileBasic::Factory(Formats::IO::Endianness endianness) {
		assert(endianness == Formats::IO::Endianness::LITTLE || endianness == Formats::IO::Endianness::BIG);

		if (endianness == Formats::IO::Endianness::LITTLE) {
			return std::make_shared<TotkToolkit::IO::Streams::File::Little>(mFile);
		}
		else {
			return std::make_shared<TotkToolkit::IO::Streams::File::Big>(mFile);
		}
	}

	void FileBasic::ReadBytes(void* out, F_U32 length) {
		mFile->read(reinterpret_cast<F_S8*>(out), length);
	}
	void FileBasic::WriteBytes(const void* in, F_U32 length) {
		mFile->write(reinterpret_cast<const F_S8*>(in), length);
	}

	std::shared_ptr<F_U8[]> FileBasic::GetBuffer() {
		F_U64 length = GetBufferLength();
		assert(length != -1); // Not sure what we should do in this case..

		F_U8* buffer = new F_U8[length];
		mFile->seekg(0);
		mFile->seekp(0); // I like to keep the two synced up.
		mFile->read(reinterpret_cast<F_S8*>(buffer), length);

		return std::shared_ptr<F_U8[]>(buffer);
	}
	F_UT FileBasic::GetBufferLength() {
		std::streampos begin = mFile->tellg();
		mFile->seekg(0, std::ios::end);
		std::streampos end = mFile->tellg();
		return end - begin;
	}
}