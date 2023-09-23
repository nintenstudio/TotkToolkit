#pragma once

#include <Formats/Resources/TXTG/TXTG.h>
#include <Formats/Aliases/Primitives.h>
#include <map>
#include <string>
#include <memory>

namespace TotkToolkit::Resources {
    class TexToGo {
    public:
        static void Init();
        
        static std::shared_ptr<Formats::Resources::TXTG::TXTG> GetTXTG(std::string name);
        static std::shared_ptr<Formats::Resources::TXTG::TXTG> GetTXTGByFilepath(std::string filepath);

    protected:
        static std::map<std::string, std::shared_ptr<Formats::Resources::TXTG::TXTG>> mCache;
    };
}