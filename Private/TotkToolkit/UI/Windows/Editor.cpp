#pragma once

#include <TotkToolkit/UI/Windows/Editor.h>

#include <memory>

namespace TotkToolkit::UI::Windows {
	Editor::Editor(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open) : TotkToolkit::IO::Editor(fileHandle), TotkToolkit::UI::Window(name, open) {
	}
}