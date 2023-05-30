#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

namespace TotkToolkit::UI::Windows::Editors {
    class PlainText : public TotkToolkit::UI::Windows::Editors::Text {
public:
        PlainText(std::string name, bool* open);

        virtual bool Parse(std::iostream* stream) override;
        virtual bool Serialize(std::iostream* stream) override;
    };
}