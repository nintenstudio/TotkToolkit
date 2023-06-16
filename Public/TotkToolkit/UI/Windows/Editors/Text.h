#pragma once

#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/UI/Windows/Editor.h>

#include <string>
#include <TextEditor.h>

namespace TotkToolkit::UI::Windows::Editors {
    class Text : public TotkToolkit::UI::Windows::Editor {
public:
        Text(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

        virtual void Draw() override;
        virtual void DrawContents() override;

protected:
        std::string mSavedText;
        ImGuiColorTextEdit::TextEditor mTextEditor;
        bool mTextEditorModified;
    };
}