#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

#include <Formats/Resources/BYML/BYML.h>
#include <memory>

namespace TotkToolkit::UI::Windows::Editors {
    class BYML : public TotkToolkit::UI::Windows::Editors::Text {
    public:
        BYML(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

        virtual bool Parse() override;
        virtual bool Serialize() override;

    protected:
        std::shared_ptr<Formats::Resources::BYML::BYML> mBYML;
    };
}