#include <TotkToolkit/UI/Windows/Editors/PlainText.h>

namespace TotkToolkit::UI::Windows::Editors {
	PlainText::PlainText(std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(name, open) {

	}

	bool PlainText::Parse(std::iostream* stream) {

		return true;
	}

	bool PlainText::Serialize(std::iostream* stream) {

		return true;
	}
}