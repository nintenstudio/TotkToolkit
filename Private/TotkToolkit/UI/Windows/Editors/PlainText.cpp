#include <TotkToolkit/UI/Windows/Editors/PlainText.h>

namespace TotkToolkit::UI::Windows::Editors {
	PlainText::PlainText(std::string name) : TotkToolkit::UI::Windows::Editors::Text(name) {

	}

	bool PlainText::Parse(Formats::IO::BinaryIOStream& stream) {

		return true;
	}

	bool PlainText::Serialize(Formats::IO::BinaryIOStream& stream) {

		return true;
	}
}