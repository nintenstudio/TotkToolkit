#include <TotkToolkit/UI/Windows/Editors/PlainText.h>

namespace TotkToolkit::UI::Windows::Editors {
	PlainText::PlainText(std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(name, open) {

	}

	bool PlainText::Parse(Formats::IO::BinaryIOStream& stream) {

		return true;
	}

	bool PlainText::Serialize(Formats::IO::BinaryIOStream& stream) {

		return true;
	}
}