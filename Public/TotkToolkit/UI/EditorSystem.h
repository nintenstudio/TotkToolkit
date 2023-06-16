#pragma once

#include <TotkToolkit/UI/Windows/Editor.h>
#include <TotkToolkit/Messaging/ExternalReceivers/UI/EditorSystem.h>
#include <vector>
#include <memory>

namespace TotkToolkit::UI {
	class EditorSystem {
	public:
		static void Init();

		static void Draw();
		static void AddEditor(std::shared_ptr<TotkToolkit::UI::Windows::Editor> editor);

	protected:
		static std::vector<std::shared_ptr<TotkToolkit::UI::Windows::Editor>> sEditors;

		static TotkToolkit::Messaging::ExternalReceivers::UI::EditorSystem sExternalReceiver;
	};
}