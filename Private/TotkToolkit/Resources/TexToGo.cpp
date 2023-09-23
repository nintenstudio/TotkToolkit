#include <TotkToolkit/Resources/TexToGo.h>

#include <TotkToolkit/IO/Filesystem.h>
#include <filesystem>

namespace TotkToolkit::Resources {
    void TexToGo::Init() {
        
    }

    std::shared_ptr<Formats::Resources::TXTG::TXTG> TexToGo::GetTXTG(std::string name) {
        std::string filepath = "romfs/TexToGo/" + name + ".txtg";

        if (mCache.contains(filepath)) {
            return mCache.at(filepath);
        }
        
        std::shared_ptr<Formats::IO::Stream> stream = TotkToolkit::IO::Filesystem::GetReadStream(filepath);
        std::shared_ptr<Formats::Resources::TXTG::TXTG> txtg = Formats::Resources::TXTG::TXTG::Factory(stream);

        mCache.insert({filepath, txtg});

        return txtg;
    }

    std::shared_ptr<Formats::Resources::TXTG::TXTG> TexToGo::GetTXTGByFilepath(std::string filepath) {
        if (mCache.contains(filepath)) {
            return mCache.at(filepath);
        }
        
        std::shared_ptr<Formats::IO::Stream> stream = TotkToolkit::IO::Filesystem::GetReadStream(filepath);
        std::shared_ptr<Formats::Resources::TXTG::TXTG> txtg = Formats::Resources::TXTG::TXTG::Factory(stream);

        mCache.insert({filepath, txtg});

        return txtg;
    }

    std::map<std::string, std::shared_ptr<Formats::Resources::TXTG::TXTG>> TexToGo::mCache;
}