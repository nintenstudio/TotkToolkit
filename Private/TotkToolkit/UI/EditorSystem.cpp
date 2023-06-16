#include <TotkToolkit/UI/EditorSystem.h>

#include <TotkToolkit/Messaging/NoticeBoard.h>

namespace TotkToolkit::UI {
	void EditorSystem::Init() {
		TotkToolkit::Messaging::NoticeBoard::AddReceiver(&sExternalReceiver);
	}

	void EditorSystem::Draw() {
		for (F_S32 i = sEditors.size() - 1; i >= 0; i--) {
			if (!sEditors[i]->IsOpen())
				sEditors.erase(sEditors.begin() + i);
		}

		for (std::shared_ptr<TotkToolkit::UI::Windows::Editor> editor : sEditors)
			editor->Draw();
	}

	void EditorSystem::AddEditor(std::shared_ptr<TotkToolkit::UI::Windows::Editor> editor) {
		sEditors.push_back(editor);
	}



	std::vector<std::shared_ptr<TotkToolkit::UI::Windows::Editor>> EditorSystem::sEditors;

	TotkToolkit::Messaging::ExternalReceivers::UI::EditorSystem EditorSystem::sExternalReceiver;
}