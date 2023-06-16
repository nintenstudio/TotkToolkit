#include <TotkToolkit/UI/Windows/Editors/PlainText.h>

namespace TotkToolkit::UI::Windows::Editors {
	PlainText::PlainText(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(fileHandle, name, open) {

	}

	bool PlainText::Parse() {

		return true;
	}

	bool PlainText::Serialize() {

		return true;
	}
}