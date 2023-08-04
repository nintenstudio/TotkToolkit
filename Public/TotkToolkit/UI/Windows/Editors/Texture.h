#pragma once

#include <TotkToolkit/UI/Window.h>
#include <TotkToolkit/UI/Windows/Editor.h>

#include <imgui.h>
#include <string>

namespace TotkToolkit::UI::Windows::Editors {
    class Texture : public TotkToolkit::UI::Windows::Editor {
    public:
        Texture(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

        virtual void DrawContents() override;

    protected:
        ImTextureID mTextureID;
    };
}