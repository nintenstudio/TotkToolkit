#pragma once

#include <TotkToolkit/UI/Windows/Editor.h>

#include <imgui.h>
#include <memory>

namespace TotkToolkit::UI::Windows {
	Editor::Editor(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::IO::Editor(fileHandle), TotkToolkit::UI::Window(name, open) {
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