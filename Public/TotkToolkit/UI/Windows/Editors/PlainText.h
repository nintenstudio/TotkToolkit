#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

namespace TotkToolkit::UI::Windows::Editors {
    class PlainText : public TotkToolkit::UI::Windows::Editors::Text {
public:
        PlainText(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

        virtual bool Parse() override;
        virtual bool Serialize() override;
    };
}