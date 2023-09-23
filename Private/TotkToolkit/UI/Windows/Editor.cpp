#include <TotkToolkit/UI/Windows/Editor.h>

#include <imgui.h>

namespace TotkToolkit::UI::Windows {
	Editor::Editor(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::IO::Editor(fileHandle), TotkToolkit::UI::Window(name, open) {
		mWindowFlags |= ImGuiWindowFlags_MenuBar;
	}
	Editor::Editor(std::shared_ptr<Formats::Resource> resource, std::string name, bool* open) : TotkToolkit::IO::Editor(resource), TotkToolkit::UI::Window(name, open) {
		mWindowFlags |= ImGuiWindowFlags_MenuBar;
	}

	void Editor::DrawContents() {
		ImGui::PushID(GetIdentifier().c_str());
		ImGui::BeginMenuBar();
		if (ImGui::MenuItem("Save"))
			Serialize();
		ImGui::EndMenuBar();
		ImGui::PopID();
	}
}