#include <TotkToolkit/UI/Windows/Editors/BYML.h>

namespace TotkToolkit::UI::Windows::Editors {
	BYML::BYML(std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(name, open) {

	}

	bool BYML::Parse(std::iostream* stream) {
		mBYML = Formats::Resources::BYML::BYML::Factory(stream);
		return mBYML != nullptr;
	}

	bool BYML::Serialize(std::iostream* stream) {
		mBYML->SetStream(stream);
		return mBYML->Serialize();
	}
}