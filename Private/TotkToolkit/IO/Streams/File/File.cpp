#include <TotkToolkit/IO/Streams/File/File.h>

#include <TotkToolkit/IO/Streams/File/EndianReaders/Little.h>
#include <TotkToolkit/IO/Streams/File/EndianReaders/Big.h>
#include <cassert>

namespace TotkToolkit::IO::Streams::File {
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

	void File::SetEndianness(Formats::IO::Endianness endianness) {
		switch (endianness) {
            case Formats::IO::Endianness::LITTLE:
                mEndianReader = std::make_shared<TotkToolkit::IO::Streams::File::EndianReaders::Little>(this);
                break;
            case Formats::IO::Endianness::BIG:
                mEndianReader = std::make_shared<TotkToolkit::IO::Streams::File::EndianReaders::Big>(this);
                break;
            default:
                assert(false); // endianness is invalid!
        }
	}

	void File::ReadBytes(void* out, F_U32 size) {
		mFile->read(reinterpret_cast<F_S8*>(out), size);
	}
	void File::WriteBytes(const void* in, F_U32 size) {
		mFile->write(reinterpret_cast<const F_S8*>(in), size);
	}

	std::shared_ptr<F_U8[]> File::GetBuffer() {
		PushSeek(0);

		F_UT length = GetBufferLength();
		std::shared_ptr<F_U8[]> res = std::shared_ptr<F_U8[]>(new F_U8[length]);
		mFile->read(reinterpret_cast<char*>(res.get()), length);

		PopSeek();
		return res;
	}
	F_UT File::GetBufferLength() {
		PushSeek(std::ios::end);
		return PopSeek();
	}
}