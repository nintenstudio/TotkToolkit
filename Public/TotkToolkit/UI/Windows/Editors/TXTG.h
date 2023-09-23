#pragma once

#include <TotkToolkit/UI/Windows/Editors/Texture.h>

#include <Formats/Resources/TXTG/TXTG.h>
#include <Formats/Aliases/Primitives.h>
#include <memory>
#include <vector>

namespace TotkToolkit::UI::Windows::Editors {
    class TXTG : public TotkToolkit::UI::Windows::Editors::Texture {
    public:
        TXTG(TotkToolkit::IO::FileHandle fileHandle, std::string name, bool* open);
        TXTG(std::shared_ptr<Formats::Resources::TXTG::TXTG> txtg, std::string name, bool* open);

        virtual void DrawContents() override;
        virtual bool Parse() override;
        virtual bool Serialize() override;

    protected:
        std::shared_ptr<Formats::Resources::TXTG::TXTG> mTXTG;
        std::vector<ImTextureID> mMips;

    private:
        F_S32 mMipSliderValue = 0;
    };
}