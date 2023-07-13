#include <TotkToolkit/IO/Streams/File/File.h>

#include <TotkToolkit/IO/Streams/File/Little.h>
#include <TotkToolkit/IO/Streams/File/Big.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::File {
	std::shared_ptr<Formats::IO::BinaryIOStream> File::Factory(std::string filePath, Formats::IO::Endianness endianness) {
		assert(endianness == Formats::IO::Endianness::LITTLE || endianness == Formats::IO::Endianness::BIG);

		if (endianness == Formats::IO::Endianness::LITTLE)
			return std::make_shared<TotkToolkit::IO::Streams::File::Little>(filePath);
		else
			return std::make_shared<TotkToolkit::IO::Streams::File::Big>(filePath);
	}
	File::File(std::shared_ptr<std::fstream> file) : mFile(file) {

	}
	File::File(std::string filePath) : mFile(new std::fstream(filePath, std::ios::in | std::ios::out | std::ios::binary)) {

	}

	void File::Seek(std::streampos pos) {
		mFile->seekg(pos);
		mFile->seekp(pos);
	}
	void File::PushSeek(std::streampos pos) {
		mSeekStack.push_back(mFile->tellg());

		mFile->seekg(pos);
		mFile->seekp(pos);
	}
	std::streampos File::PopSeek() {
		std::streampos res = mFile->tellg();

		mFile->seekg(mSeekStack.back());
		mFile->seekp(mSeekStack.back());
		mSeekStack.pop_back();

		return res;
	}
	std::streampos File::GetSeek() {
		return mFile->tellg();
	}
	void File::AlignSeek(std::streampos alignment) {
		std::streampos pos = mFile->tellg();
		pos = (pos % alignment == 0) ? pos : alignment - (pos % alignment) + pos;
		Seek(pos);
	}
	std::string File::ReadZeroTerminatedString(F_U32 allocation) {
		std::string res;
		res.reserve(allocation);

		char currentChar;
		while (mFile->read(&currentChar, 1), currentChar != '\0') {
			res += currentChar;
		}

		return res;
	}
	void File::WriteZeroTerminatedString(std::string value) {
		mFile->write(value.c_str(), value.length() + 1);
	}

	void File::ReadBytes(void* out, F_U32 size) {
		mFile->read(reinterpret_cast<F_S8*>(out), size);
	}
	void File::WriteBytes(const void* in, F_U32 size) {
		mFile->write(reinterpret_cast<const F_S8*>(in), size);
	}
}