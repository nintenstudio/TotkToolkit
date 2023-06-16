#include <TotkToolkit/UI/Windows/Editors/BYML.h>

#include <imgui.h>

namespace TotkToolkit::UI::Windows::Editors {
	BYML::BYML(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::UI::Windows::Editors::Text(fileHandle, name, open) {
		mTextEditor.SetLanguageDefinition(ImGuiColorTextEdit::TextEditor::LanguageDefinition::Yaml());
	}

	bool BYML::Parse() {
		mBYML = Formats::Resources::BYML::BYML::Factory(mFileHandle.GetReadStream());
		if (mBYML == nullptr)
			return false;

		mSavedText = mBYML->ToYAML();
		mTextEditor.SetText(mSavedText);

		return true;
	}

	bool BYML::Serialize() {
		mBYML->SetStream(mFileHandle.GetWriteStream());
		return mBYML->Serialize();
	}
}