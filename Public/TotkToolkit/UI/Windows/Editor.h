#pragma once

#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/IO/Editor.h>

namespace TotkToolkit::UI::Windows {
	class Editor : public TotkToolkit::IO::Editor, public TotkToolkit::UI::Window {
	public:
		Editor(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

		virtual void DrawContents() override;
	};
}