#pragma once

#include <TotkToolkit/UI/Windows/Editors/Texture.h>

#include <Formats/Resources/TXTG/TXTG.h>
#include <memory>

namespace TotkToolkit::UI::Windows::Editors {
    class TXTG : public TotkToolkit::UI::Windows::Editors::Texture {
    public:
        TXTG(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);

        virtual bool Parse() override;
        virtual bool Serialize() override;

    protected:
        std::shared_ptr<Formats::Resources::TXTG::TXTG> mTXTG;
    };
}