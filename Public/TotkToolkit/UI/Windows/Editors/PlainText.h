#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

namespace TotkToolkit::UI::Windows::Editors {
    class PlainText : public TotkToolkit::UI::Windows::Editors::Text {
public:
        PlainText(std::string name, bool* open);

        virtual bool Parse(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) override;
        virtual bool Serialize(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) override;
    };
}