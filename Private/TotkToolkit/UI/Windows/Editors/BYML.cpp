#include <TotkToolkit/UI/Windows/Editors/BYML.h>

#include <imgui.h>

namespace TotkToolkit::UI::Windows::Editors {
	BYML::BYML(std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(name, open) {
		mTextEditor.SetLanguageDefinition(ImGuiColorTextEdit::TextEditor::LanguageDefinition::Yaml());
	}

	bool BYML::Parse(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) {
		mBYML = Formats::Resources::BYML::BYML::Factory(stream);
		if (mBYML == nullptr)
			return false;

		mSavedText = mBYML->ToYAML();
		mTextEditor.SetText(mSavedText);

		return true;
	}

	bool BYML::Serialize(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) {
		mBYML->SetStream(stream);
		return mBYML->Serialize();
	}
}