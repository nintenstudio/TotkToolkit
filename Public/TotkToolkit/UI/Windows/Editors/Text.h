#pragma once

#include <TotkToolkit/UI/Windows/Window.h>
#include <TotkToolkit/IO/Editor.h>

#include <string>
#include <TextEditor.h>

namespace TotkToolkit::UI::Windows::Editors {
    class Text : public TotkToolkit::UI::Windows::Window, public TotkToolkit::IO::Editor {
public:
        Text(std::string name, bool* open);

        virtual void DrawContents() override;

protected:
        std::string mText;
        ImGuiColorTextEdit::TextEditor mTextEditor;
    };
}