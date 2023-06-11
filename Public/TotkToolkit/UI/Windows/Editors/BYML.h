#pragma once

#include <TotkToolkit/UI/Windows/Editors/Text.h>

#include <Formats/Resources/BYML/BYML.h>
#include <memory>

namespace TotkToolkit::UI::Windows::Editors {
    class BYML : public TotkToolkit::UI::Windows::Editors::Text {
    public:
        BYML(std::string name, bool* open);

        virtual bool Parse(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) override;
        virtual bool Serialize(std::shared_ptr<TotkToolkit::IO::Streams::Physfs::PhysfsBasic> stream) override;

    protected:
        std::shared_ptr<Formats::Resources::BYML::BYML> mBYML;
    };
}