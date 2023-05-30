#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

#include <string>

namespace TotkToolkit::UI::Windows::Editors {
    class PlainText : public TotkToolkit::UI::Windows::Editors::Text {
public:
        PlainText(std::string name, bool* open);

        virtual bool Parse(Formats::IO::BinaryIOStream& stream) override;
        virtual bool Serialize(Formats::IO::BinaryIOStream& stream) override;
    };
}